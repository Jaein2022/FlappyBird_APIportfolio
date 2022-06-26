#include "PreCompile.h"
#include "GameEngineCollisionBody.h"
#include "GameEngineActor.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineWindow.h"
#include "GameEngineLevel.h"

std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
	GameEngineCollisionBody::collisionFunctions_
	[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)] = { nullptr };

bool GameEngineCollisionBody::isRenderingOn_ = false;

GameEngineCollisionBody::GameEngineCollisionBody(GameEngineActor* _actor)
	: parentActor_(_actor),
	localPos_(float4::Zero),
	size_(float4::Zero),
	isCollided_(false),
	type_(CollisionBodyType::MAX),
	collisionBody_(),
	angle_(0.f),
	isCameraEffect_(false),
	mainPen_(NULL),
	prevPen_(NULL),
	normalColor_(NULL),
	responseColor_(NULL),
	thickness_(0)
{
	SetParent(_actor);
}

GameEngineCollisionBody::~GameEngineCollisionBody()
{
	DeleteObject(mainPen_);
	DeleteObject(prevPen_);
}

void GameEngineCollisionBody::Initialize()
{

	collisionFunctions_[static_cast<int>(CollisionBodyType::FRect)][static_cast<int>(CollisionBodyType::FRect)]
		= std::bind(&GameEngineCollisionBody::FRectToFRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::FRect)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::FRectToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::FRect)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::FRectToVLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::FRect)][static_cast<int>(CollisionBodyType::RRect)]
		= std::bind(&GameEngineCollisionBody::FRectToRRect, std::placeholders::_1, std::placeholders::_2);


	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::FRect)]
		= std::bind(&GameEngineCollisionBody::HLineToFRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::HLineToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::HLineToVLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::HLine)][static_cast<int>(CollisionBodyType::RRect)]
		= std::bind(&GameEngineCollisionBody::HLineToRRect, std::placeholders::_1, std::placeholders::_2);


	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::FRect)]
		= std::bind(&GameEngineCollisionBody::VLineToFRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::VLineToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::VLineToVLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::VLine)][static_cast<int>(CollisionBodyType::RRect)]
		= std::bind(&GameEngineCollisionBody::VLineToRRect, std::placeholders::_1, std::placeholders::_2);


	collisionFunctions_[static_cast<int>(CollisionBodyType::RRect)][static_cast<int>(CollisionBodyType::FRect)]
		= std::bind(&GameEngineCollisionBody::RRectToFRect, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::RRect)][static_cast<int>(CollisionBodyType::HLine)]
		= std::bind(&GameEngineCollisionBody::RRectToHLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::RRect)][static_cast<int>(CollisionBodyType::VLine)]
		= std::bind(&GameEngineCollisionBody::RRectToVLine, std::placeholders::_1, std::placeholders::_2);

	collisionFunctions_[static_cast<int>(CollisionBodyType::RRect)][static_cast<int>(CollisionBodyType::RRect)]
		= std::bind(&GameEngineCollisionBody::RRectToRRect, std::placeholders::_1, std::placeholders::_2);

}

void GameEngineCollisionBody::Render()
{
	if (false == isRenderingOn_)
	{
		return;
	}

	GameEngineImage* backBufferImage = GameEngineImageManager::GetInst().GetBackBufferImage();
	
	float4 renderPos = float4(collisionBody_.AABB.Center.x, collisionBody_.AABB.Center.y);
	if (true == isCameraEffect_)
	{
		renderPos -= parentActor_->GetLevel()->GetCameraPos();
	}

	prevPen_ = static_cast<HPEN>(SelectObject(
		backBufferImage->GetHDC(),
		static_cast<HGDIOBJ>(mainPen_))
	);

	GameEngineRect renderRect = GameEngineRect(renderPos, size_);

	switch (type_)
	{
	case CollisionBodyType::FRect:
	{
		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.ITop(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.ITop()
		);		
		
		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.ITop(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.IBot()
		);		
		
		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.IBot(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.IBot()
		);		
		
		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.IBot(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.ITop()
		);


		break;
	}
	
	case CollisionBodyType::HLine:
	{
		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.ITop(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.ITop()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.ITop(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.IBot()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.IBot(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.IBot()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.IBot(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.ITop()
		);

		break;
	}

	case CollisionBodyType::VLine:
	{
		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.ITop(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.ITop()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.ITop(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.IBot()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.IRight(),
			renderRect.IBot(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.IBot()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.IBot(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			renderRect.ILeft(),
			renderRect.ITop()
		);
		break;
	}
	case CollisionBodyType::RRect:
	{
		DirectX::XMVECTOR rRectQuaternionRotation = DirectX::XMLoadFloat4(
			&(this->collisionBody_.OBB.Orientation));

		DirectX::XMVECTOR rRectAxis;
		float radianAngle;
		DirectX::XMQuaternionToAxisAngle(&rRectAxis, &radianAngle, rRectQuaternionRotation);
	
		GameEngineRect renderOBB = GameEngineRect(
			float4::Zero, 
			float4(this->collisionBody_.OBB.Extents.x * 2.f, 
				this->collisionBody_.OBB.Extents.y * 2.f)
		);

		if (0.0f > rRectAxis.m128_f32[2])
		{
			radianAngle = -radianAngle;
		}

		float4 lt = renderPos + renderOBB.GetLeftTop().Rotate2DByRadian(radianAngle);
		float4 rt = renderPos + renderOBB.GetRightTop().Rotate2DByRadian(radianAngle);
		float4 lb = renderPos + renderOBB.GetLeftBot().Rotate2DByRadian(radianAngle);
		float4 rb = renderPos + renderOBB.GetRightBot().Rotate2DByRadian(radianAngle);


		MoveToEx(
			backBufferImage->GetHDC(),
			lt.IntX(),
			lt.IntY(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			rt.IntX(),
			rt.IntY()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			rt.IntX(),
			rt.IntY(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			rb.IntX(),
			rb.IntY()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			rb.IntX(),
			rb.IntY(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			lb.IntX(),
			lb.IntY()
		);

		MoveToEx(
			backBufferImage->GetHDC(),
			lb.IntX(),
			lb.IntY(),
			nullptr
		);
		LineTo(
			backBufferImage->GetHDC(),
			lt.IntX(),
			lt.IntY()
		);

		break;
	}


	default:
		GameEngineDebug::MsgBoxError("구현되지 않은 충돌체 형식입니다.");
		break;
	}

	mainPen_ = static_cast<HPEN>(SelectObject(
		backBufferImage->GetHDC(),
		static_cast<HGDIOBJ>(prevPen_)));
}

void GameEngineCollisionBody::Reset()
{
	isCollided_ = false;
	SwitchColor();
	IncludeUpdate();
}

void GameEngineCollisionBody::Respond(bool _isExcluded /*= false*/)
{
	isCollided_ = true;
	SwitchColor();
	if (true == _isExcluded)
	{
		ExcludeUpdate();
	}
}

void GameEngineCollisionBody::SetTypeAndSize(CollisionBodyType _type, const float4& _size)
{
	type_ = _type;
	size_ = _size;

	switch (type_)
	{
	case CollisionBodyType::FRect:
	{
		collisionBody_.AABB.Center = DirectX::XMFLOAT3(
			this->GetActor()->GetWorldPos().x + localPos_.x,
			this->GetActor()->GetWorldPos().y + localPos_.y,
			0.f
		);
		collisionBody_.AABB.Extents = DirectX::XMFLOAT3(size_.Half_X(), size_.Half_Y(), 1.f);
		break;
	}

	case CollisionBodyType::HLine:
	{
		collisionBody_.AABB.Center = DirectX::XMFLOAT3(
			this->GetActor()->GetWorldPos().x + localPos_.x,
			this->GetActor()->GetWorldPos().y + localPos_.y,
			0.f
		);
		collisionBody_.AABB.Extents = DirectX::XMFLOAT3(size_.Half_X(), 2.f, 1.f);
		break;
	}

	case CollisionBodyType::VLine:
	{
		collisionBody_.AABB.Center = DirectX::XMFLOAT3(
			this->GetActor()->GetWorldPos().x + localPos_.x,
			this->GetActor()->GetWorldPos().y + localPos_.y,
			0.f
		);
		collisionBody_.AABB.Extents = DirectX::XMFLOAT3(2.f, size_.Half_Y(), 1.f);
		break;
	}

	case CollisionBodyType::RRect:
	{
		collisionBody_.OBB.Center = DirectX::XMFLOAT3(
			this->GetActor()->GetWorldPos().x + localPos_.x,
			this->GetActor()->GetWorldPos().y + localPos_.y,
			0.f
		);
		collisionBody_.OBB.Extents = DirectX::XMFLOAT3(size_.Half_X(), size_.Half_Y(), 1.f);
		break;
	}

	default:
		GameEngineDebug::MsgBoxError("생성할 수 없는 타입의 충돌체입니다.");
		return;
	}
}

void GameEngineCollisionBody::SetRrectAngle(float _degree)
{
	angle_ = _degree;

	DirectX::XMFLOAT4 obbOrientation;

	DirectX::XMStoreFloat4(
		&obbOrientation,
		DirectX::XMQuaternionRotationRollPitchYaw(
			0.f, 0.f, angle_ * GameEngineMath::DegreeToRadian)
	);

	this->collisionBody_.OBB.Orientation = obbOrientation;
}

void GameEngineCollisionBody::SwitchColor()
{
	DeleteObject(mainPen_);
	if (true == isCollided_)
	{
		mainPen_ = CreatePen(PS_SOLID, thickness_, responseColor_);
	}
	else
	{
		mainPen_ = CreatePen(PS_SOLID, thickness_, normalColor_);
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

bool GameEngineCollisionBody::FRectToFRect(GameEngineCollisionBody* _fRectA, GameEngineCollisionBody* _fRectB)
{
	_fRectA->collisionBody_.AABB.Center.x = _fRectA->GetWorldPos().x;
	_fRectA->collisionBody_.AABB.Center.y = _fRectA->GetWorldPos().y;

	_fRectB->collisionBody_.AABB.Center.x = _fRectB->GetWorldPos().x;
	_fRectB->collisionBody_.AABB.Center.y = _fRectB->GetWorldPos().y;

	return _fRectA->collisionBody_.AABB.Intersects(_fRectB->collisionBody_.AABB);
}

bool GameEngineCollisionBody::FRectToHLine(GameEngineCollisionBody* _fRect, GameEngineCollisionBody* _hLine)
{
	_fRect->collisionBody_.AABB.Center.x = _fRect->GetWorldPos().x;
	_fRect->collisionBody_.AABB.Center.y = _fRect->GetWorldPos().y;

	_hLine->collisionBody_.AABB.Center.x = _hLine->GetWorldPos().x;
	_hLine->collisionBody_.AABB.Center.y = _hLine->GetWorldPos().y;

	return _fRect->collisionBody_.AABB.Intersects(_hLine->collisionBody_.AABB);
}

bool GameEngineCollisionBody::FRectToVLine(GameEngineCollisionBody* _fRect, GameEngineCollisionBody* _vLine)
{
	_fRect->collisionBody_.AABB.Center.x = _fRect->GetWorldPos().x;
	_fRect->collisionBody_.AABB.Center.y = _fRect->GetWorldPos().y;

	_vLine->collisionBody_.AABB.Center.x = _vLine->GetWorldPos().x;
	_vLine->collisionBody_.AABB.Center.y = _vLine->GetWorldPos().y;

	return _fRect->collisionBody_.AABB.Intersects(_vLine->collisionBody_.AABB);
}

bool GameEngineCollisionBody::FRectToRRect(GameEngineCollisionBody* _fRect, GameEngineCollisionBody* _rRect)
{
	_fRect->collisionBody_.AABB.Center.x = _fRect->GetWorldPos().x;
	_fRect->collisionBody_.AABB.Center.y = _fRect->GetWorldPos().y;

	_rRect->collisionBody_.OBB.Center.x = _rRect->GetWorldPos().x;
	_rRect->collisionBody_.OBB.Center.y = _rRect->GetWorldPos().y;

	return _fRect->collisionBody_.AABB.Intersects(_rRect->collisionBody_.OBB);
}

bool GameEngineCollisionBody::HLineToFRect(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _fRect)
{
	_hLine->collisionBody_.AABB.Center.x = _hLine->GetWorldPos().x;
	_hLine->collisionBody_.AABB.Center.y = _hLine->GetWorldPos().y;

	_fRect->collisionBody_.AABB.Center.x = _fRect->GetWorldPos().x;
	_fRect->collisionBody_.AABB.Center.y = _fRect->GetWorldPos().y;

	return _hLine->collisionBody_.AABB.Intersects(_fRect->collisionBody_.AABB);
}

bool GameEngineCollisionBody::HLineToHLine(GameEngineCollisionBody* _hLineA, GameEngineCollisionBody* _hLineB)
{
	//return _hLineA->collisionBody_.AABB.Intersects(_hLineB->collisionBody_.AABB);
	return false;
}

bool GameEngineCollisionBody::HLineToVLine(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _vLine)
{
	//return _hLine->collisionBody_.AABB.Intersects(_vLine->collisionBody_.AABB);
	return false;
}

bool GameEngineCollisionBody::HLineToRRect(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _rRect)
{
	_hLine->collisionBody_.AABB.Center.x = _hLine->GetWorldPos().x;
	_hLine->collisionBody_.AABB.Center.y = _hLine->GetWorldPos().y;

	_rRect->collisionBody_.OBB.Center.x = _rRect->GetWorldPos().x;
	_rRect->collisionBody_.OBB.Center.y = _rRect->GetWorldPos().y;

	return _hLine->collisionBody_.AABB.Intersects(_rRect->collisionBody_.OBB);
}

bool GameEngineCollisionBody::VLineToFRect(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _fRect)
{
	_vLine->collisionBody_.AABB.Center.x = _vLine->GetWorldPos().x;
	_vLine->collisionBody_.AABB.Center.y = _vLine->GetWorldPos().y;

	_fRect->collisionBody_.AABB.Center.x = _fRect->GetWorldPos().x;
	_fRect->collisionBody_.AABB.Center.y = _fRect->GetWorldPos().y;

	return _vLine->collisionBody_.AABB.Intersects(_fRect->collisionBody_.AABB);
}

bool GameEngineCollisionBody::VLineToHLine(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _hLine)
{
	//return _vLine->collisionBody_.AABB.Intersects(_hLine->collisionBody_.AABB);
	return false;
}

bool GameEngineCollisionBody::VLineToVLine(GameEngineCollisionBody* _vLineA, GameEngineCollisionBody* _vLineB)
{
	//return _vLineA->collisionBody_.AABB.Intersects(_vLineB->collisionBody_.AABB);
	return false;
}

bool GameEngineCollisionBody::VLineToRRect(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _rRect)
{
	_vLine->collisionBody_.AABB.Center.x = _vLine->GetWorldPos().x;
	_vLine->collisionBody_.AABB.Center.y = _vLine->GetWorldPos().y;

	_rRect->collisionBody_.OBB.Center.x = _rRect->GetWorldPos().x;
	_rRect->collisionBody_.OBB.Center.y = _rRect->GetWorldPos().y;

	return _vLine->collisionBody_.AABB.Intersects(_rRect->collisionBody_.OBB);
}

bool GameEngineCollisionBody::RRectToFRect(GameEngineCollisionBody* _rRect, GameEngineCollisionBody* _fRect)
{
	_rRect->collisionBody_.OBB.Center.x = _rRect->GetWorldPos().x;
	_rRect->collisionBody_.OBB.Center.y = _rRect->GetWorldPos().y;

	_fRect->collisionBody_.AABB.Center.x = _fRect->GetWorldPos().x;
	_fRect->collisionBody_.AABB.Center.y = _fRect->GetWorldPos().y;

	return _rRect->collisionBody_.OBB.Intersects(_fRect->collisionBody_.AABB);
}

bool GameEngineCollisionBody::RRectToHLine(GameEngineCollisionBody* _rRect, GameEngineCollisionBody* _hLine)
{
	_rRect->collisionBody_.OBB.Center.x = _rRect->GetWorldPos().x;
	_rRect->collisionBody_.OBB.Center.y = _rRect->GetWorldPos().y;

	_hLine->collisionBody_.AABB.Center.x = _hLine->GetWorldPos().x;
	_hLine->collisionBody_.AABB.Center.y = _hLine->GetWorldPos().y;

	return _rRect->collisionBody_.OBB.Intersects(_hLine->collisionBody_.AABB);
}

bool GameEngineCollisionBody::RRectToVLine(GameEngineCollisionBody* _rRect, GameEngineCollisionBody* _vLine)
{
	_rRect->collisionBody_.OBB.Center.x = _rRect->GetWorldPos().x;
	_rRect->collisionBody_.OBB.Center.y = _rRect->GetWorldPos().y;

	_vLine->collisionBody_.AABB.Center.x = _vLine->GetWorldPos().x;
	_vLine->collisionBody_.AABB.Center.y = _vLine->GetWorldPos().y;

	return _rRect->collisionBody_.OBB.Intersects(_vLine->collisionBody_.AABB);
}

bool GameEngineCollisionBody::RRectToRRect(GameEngineCollisionBody* _rRectA, GameEngineCollisionBody* _rRectB)
{
	_rRectA->collisionBody_.OBB.Center.x = _rRectA->GetWorldPos().x;
	_rRectA->collisionBody_.OBB.Center.y = _rRectA->GetWorldPos().y;

	_rRectB->collisionBody_.OBB.Center.x = _rRectB->GetWorldPos().x;
	_rRectB->collisionBody_.OBB.Center.y = _rRectB->GetWorldPos().y;

	return _rRectA->collisionBody_.OBB.Intersects(_rRectB->collisionBody_.OBB);
}


