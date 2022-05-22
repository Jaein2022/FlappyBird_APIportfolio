#include "PreCompile.h"
#include "Base.h"

Base::Base(): baseWidth_(336), baseHeight_(112), baseRenderer_(nullptr), baseCollisionBody_(nullptr)
{
}

Base::~Base()
{
}

void Base::Initialize()
{
	baseRenderer_ = CreateRenderer("base.bmp", "baseRenderer");
	baseRenderer_->SetRenderingImagePivot(RenderPivot::Center);


	baseCollisionBody_ = CreateCollisionBody(
		"baseCollsionBody",
		float4::RED,
		CollisionBodyType::HLine,
		{ baseWidth_, 0 }
	);
	baseCollisionBody_->SetLocalPos({ 0, -56 });



}

void Base::Update()
{
}

void Base::Render()
{
	baseRenderer_->Render();
	baseCollisionBody_->Render();
}

void Base::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
	if (_other->GetName() == "bird" && CollisionBodyType::Rect == _otherCollisionBody->GetType())
	{
		baseCollisionBody_->SetColor(float4::BLACK);
	}
}
