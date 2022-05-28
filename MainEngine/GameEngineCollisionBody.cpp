#include "PreCompile.h"
#include "GameEngineCollisionBody.h"
#include "GameEngineActor.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineWindow.h"

std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
	GameEngineCollisionBody::collisionFunctions_
	[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)] = { nullptr };

bool GameEngineCollisionBody::isRenderingOn_ = true;

GameEngineCollisionBody::GameEngineCollisionBody(GameEngineActor* _actor)
	: parentActor_(_actor),
	localPos_(float4::ZERO),
	size_(float4::ZERO),
	type_(CollisionBodyType::MAX),
	isCameraEffect_(false),
	pen_(nullptr),
	brush_(nullptr)
{
	SetParent(_actor);
}

GameEngineCollisionBody::~GameEngineCollisionBody()
{
	if (pen_ != nullptr)
	{
		DeleteObject(pen_);
	}	
	
	if (brush_ != nullptr)
	{
		DeleteObject(brush_);
	}	
}

void GameEngineCollisionBody::Initialize()
{

	collisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::RectToRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::RectToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::RectToVLine, std::placeholders::_1, std::placeholders::_2);


	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::HLineToRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::HLineToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::HLineToVLine, std::placeholders::_1, std::placeholders::_2);


	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::VLineToRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::VLineToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::VLineToVLine, std::placeholders::_1, std::placeholders::_2);

}

bool GameEngineCollisionBody::RectToRect(GameEngineCollisionBody* _rectA, GameEngineCollisionBody* _rectB)
{
	GameEngineRect rectA = _rectA->GetRect();
	GameEngineRect rectB = _rectB->GetRect();

	if (rectA.IRight() < rectB.ILeft())
	{
		return false;
	}
	if (rectA.ILeft() > rectB.IRight())
	{
		return false;
	}
	if (rectA.ITop() > rectB.IBot())
	{
		return false;
	}
	if (rectA.IBot() < rectB.ITop())
	{
		return false;
	}
	return true;
}

bool GameEngineCollisionBody::RectToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine)
{
	GameEngineRect rect = _rect->GetRect();

	float4 leftEnd = _hLine->GetWorldPos() - _hLine->GetSize().Half();
	float4 rightEnd = _hLine->GetWorldPos() + _hLine->GetSize().Half();

	if (rect.IRight() < leftEnd.IntX() || rect.ILeft() > rightEnd.IntX())
	{
		return false;
	}

	if (rect.IBot() > leftEnd.IntY() && rect.ITop() < leftEnd.IntY())
	{
		return true;
	}

	return false;
}

bool GameEngineCollisionBody::RectToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine)
{
	GameEngineRect rect = _rect->GetRect();
	float4 highEnd = _vLine->GetWorldPos() - _vLine->GetSize().Half();
	float4 lowEnd = _vLine->GetWorldPos() + _vLine->GetSize().Half();

	if (rect.IBot() < highEnd.IntY() || rect.ITop() > lowEnd.IntY())
	{
		return false;
	}
	
	if (rect.IRight() > highEnd.IntX() && rect.ILeft() < highEnd.IntX())
	{
		return true;
	}

	return false;
}

bool GameEngineCollisionBody::HLineToRect(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _rect)
{
	return RectToHLine(_rect, _hLine);
}

bool GameEngineCollisionBody::HLineToHLine(GameEngineCollisionBody* _hLineA, GameEngineCollisionBody* _hLineB)
{
	return false;
}

bool GameEngineCollisionBody::HLineToVLine(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _vLine)
{
	return false;
}

bool GameEngineCollisionBody::VLineToRect(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _rect)
{
	return RectToVLine(_rect, _vLine);
}

bool GameEngineCollisionBody::VLineToHLine(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _hLine)
{
	return false;
}

bool GameEngineCollisionBody::VLineToVLine(GameEngineCollisionBody* _vLineA, GameEngineCollisionBody* _vLineB)
{
	return false;
}

void GameEngineCollisionBody::Render()
{
	if (false == isRenderingOn_)
	{
		return;
	}

	GameEngineImage* backBufferImage = GameEngineImageManager::GetInst().GetBackBufferImage();
	

	float4 renderPos = float4::ZERO;
	if (true == isCameraEffect_)
	{
		renderPos = parentActor_->GetCameraPos() + localPos_;
	}
	else
	{
		renderPos = parentActor_->GetWorldPos() + localPos_;
	}



	switch (type_)
	{
	case CollisionBodyType::Rect:
	{
		RECT rect =
		{
			renderPos.IntX() - size_.Half_IntX(),
			renderPos.IntY() - size_.Half_IntY(),
			renderPos.IntX() + size_.Half_IntX(),
			renderPos.IntY() + size_.Half_IntY()
		};

		FrameRect(	//선 굵기는 1로 고정 되어있음.
			backBufferImage->GetHDC(),
			&rect,
			brush_
		);
		break;
	}
	
	case CollisionBodyType::HLine:
	{
		HPEN prevPen = static_cast<HPEN>(SelectObject(
			backBufferImage->GetHDC(),
			static_cast<HGDIOBJ>(pen_)
		));

		MoveToEx(
			backBufferImage->GetHDC(),
			renderPos.IntX() - size_.Half_IntX(),
			renderPos.IntY(),
			nullptr
		);

		LineTo(
			backBufferImage->GetHDC(),
			renderPos.IntX() + size_.Half_IntX(),
			renderPos.IntY()
		);

		pen_ = static_cast<HPEN>(SelectObject(
			backBufferImage->GetHDC(),
			static_cast<HGDIOBJ>(prevPen)
		));

		break;
	}

	case CollisionBodyType::VLine:
	{
		HPEN prevPen = static_cast<HPEN>(SelectObject(
			backBufferImage->GetHDC(),
			static_cast<HGDIOBJ>(pen_)
		));

		MoveToEx(
			backBufferImage->GetHDC(),
			renderPos.IntX(),
			renderPos.IntY() - size_.Half_IntY(),
			nullptr
		);

		LineTo(
			backBufferImage->GetHDC(),
			renderPos.IntX(),
			renderPos.IntY() + size_.Half_IntY()
		);

		pen_ = static_cast<HPEN>(SelectObject(
			backBufferImage->GetHDC(),
			static_cast<HGDIOBJ>(prevPen)
		));
		break;
	}

	//case CollisionBodyType::Point:
	//	//점은 선 두개 크로스해서 표시.
	//	break;


	default:
		GameEngineDebug::MsgBoxError("구현되지 않은 충돌체 형식입니다.");
		break;
	}


}

bool GameEngineCollisionBody::CheckCollision(GameEngineCollisionBody* _other)
{
	if (nullptr == this)
	{
		GameEngineDebug::MsgBoxError("충돌 주체가 없습니다.");
		return false;
	}

	if (nullptr == _other)
	{
		GameEngineDebug::MsgBoxError("충돌 객체가 없습니다.");
		return false;
	}

	return collisionFunctions_[this->GetTypeInt()][_other->GetTypeInt()](this, _other);
}

float4 GameEngineCollisionBody::GetWorldPos()
{
	return parentActor_->GetWorldPos() + localPos_;
}

GameEngineRect GameEngineCollisionBody::GetRect()
{
	return { parentActor_->GetWorldPos() + localPos_, size_ };
}