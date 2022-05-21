#include "PreCompile.h"
#include "GameEngineCollisionBody.h"
#include "GameEngineActor.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineWindow.h"

std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
	GameEngineCollisionBody::collisionFunctions_
	[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)] = { nullptr };

GameEngineCollisionBody::GameEngineCollisionBody(GameEngineActor* _actor)
	: parentActor_(_actor),
	localPos_(float4::ZERO),
	size_(float4::ZERO),
	type_(CollisionBodyType::MAX),
	isCameraEffect_(false),
	pen_(nullptr),
	brush_(nullptr),
	color_(0)
{
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
	//for (int i = 0; i < static_cast<int>(CollisionBodyType::MAX); i++)
	//{
	//	for (int j = 0; j < static_cast<int>(CollisionBodyType::MAX); j++)
	//	{
	//		collisionFunctions_[i][j] = nullptr;
	//	}
	//}

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
	//HLine은 화면상 왼쪽에서 시작해 오른쪽으로 뻗어 있다는것을 전제로 구성된 코드.
	GameEngineRect rect = _rect->GetRect();

	float4 leftEnd = _hLine->GetWorldPos();
	float4 rightEnd = _hLine->GetWorldPos() + _hLine->GetSize();

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
	//VLine은 화면상 위에서 아래로 뻗어 있다는것을 전제로 구성된 코드.
	GameEngineRect rect = _rect->GetRect();
	float4 highEnd = _vLine->GetWorldPos();
	float4 lowEnd = _vLine->GetWorldPos() + _vLine->GetSize();

	if (rect.IBot() > highEnd.IntY() || rect.ITop() < lowEnd.IntY())
	{
		return false;
	}
	
	if (rect.IRight() > highEnd.IntX() && rect.ILeft() < highEnd.IntX())
	{
		return true;
	}

	return false;
}

bool GameEngineCollisionBody::HLineToRect(GameEngineCollisionBody* _a, GameEngineCollisionBody* _b)
{
	return false;
}

bool GameEngineCollisionBody::HLineToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine)
{
	return false;
}

bool GameEngineCollisionBody::HLineToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine)
{
	return false;
}

bool GameEngineCollisionBody::VLineToRect(GameEngineCollisionBody* _a, GameEngineCollisionBody* _b)
{
	return false;
}

bool GameEngineCollisionBody::VLineToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine)
{
	return false;
}

bool GameEngineCollisionBody::VLineToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine)
{
	return false;
}

void GameEngineCollisionBody::Render()
{
	GameEngineImage* backBufferImage = GameEngineImageManager::GetInst().GetBackBufferImage();
	
	float4 renderPos = this->GetWorldPos();

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

		FrameRect(
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
			renderPos.IntX(),
			renderPos.IntY(),
			nullptr
		);

		LineTo(
			backBufferImage->GetHDC(),
			renderPos.IntX() + size_.IntX(),
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
			renderPos.IntY(),
			nullptr
		);

		LineTo(
			backBufferImage->GetHDC(),
			renderPos.IntX(),
			renderPos.IntY() + size_.IntY()
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

	//if (nullptr != collisionFunctions_[this->GetTypeInt()][_other->GetTypeInt()])
	//{
		return collisionFunctions_[this->GetTypeInt()][_other->GetTypeInt()](this, _other);
	//}
	//else
	//{
	//	GameEngineDebug::MsgBoxError("구현되지 않은 형식의 충돌입니다.");
	//	return false;
	//}
}

float4 GameEngineCollisionBody::GetWorldPos()
{
	return parentActor_->GetWorldPos() + localPos_;
}

GameEngineRect GameEngineCollisionBody::GetRect()
{
	return { parentActor_->GetWorldPos() + localPos_, size_ };
}