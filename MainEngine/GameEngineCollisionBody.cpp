#include "PreCompile.h"
#include "GameEngineCollisionBody.h"
#include "GameEngineActor.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineWindow.h"

std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
GameEngineCollisionBody::collisionFunctions_[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)]
= { nullptr };

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
	for (int i = 0; i < static_cast<int>(CollisionBodyType::MAX); i++)
	{
		for (int j = 0; j < static_cast<int>(CollisionBodyType::MAX); j++)
		{
			collisionFunctions_[i][j] = nullptr;
		}
	}

	collisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::RectToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::RectToRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::HLineToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::HLineToRect, std::placeholders::_1, std::placeholders::_2);

}

bool GameEngineCollisionBody::RectToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine)
{
	Figure rect = _rect->GetFigure();
	Figure hLine = _hLine->GetFigure();

	if (rect.IRight() < hLine.ILeft())
	{
		return false;
	}
	if (rect.ILeft() > hLine.IRight())
	{
		return false;
	}
	if (rect.ITop() > hLine.pos_.y)
	{
		return false;
	}
	if (rect.IBot() < hLine.pos_.y)
	{
		return false;
	}

	return true;
}

bool GameEngineCollisionBody::RectToRect(GameEngineCollisionBody* _rectA, GameEngineCollisionBody* _rectB)
{
	Figure rectA = _rectA->GetFigure();
	Figure rectB = _rectB->GetFigure();

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

bool GameEngineCollisionBody::HLineToHLine(GameEngineCollisionBody* _hLineA, GameEngineCollisionBody* _hLineB)
{
	GameEngineDebug::MsgBoxError("아직 구현하지 않은 충돌체크함수를 이용하려고 합니다.");
	return false;
}

bool GameEngineCollisionBody::HLineToRect(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _rect)
{
	GameEngineDebug::MsgBoxError("아직 구현하지 않은 충돌체크함수를 이용하려고 합니다.");
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

	return collisionFunctions_[this->GetType()][_other->GetType()](this, _other);
}

float4 GameEngineCollisionBody::GetWorldPos()
{
	return parentActor_->GetWorldPos() + localPos_;
}

Figure GameEngineCollisionBody::GetFigure()
{
	return { parentActor_->GetWorldPos() + localPos_, size_ };
}