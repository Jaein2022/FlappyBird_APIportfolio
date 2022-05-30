#include "PreCompile.h"
#include "Base.h"

Base::Base(): baseWidth_(336), baseHeight_(112), base_Renderer_(nullptr), base_CollisionBody_(nullptr)
{
}

Base::~Base()
{
}

void Base::Initialize()
{
	base_Renderer_ = CreateRenderer("base.bmp", "base_Renderer");
	base_Renderer_->SetRenderPivot(RenderPivot::Center);
	base_Renderer_->SetCameraEffectOn();

	base_CollisionBody_ = CreateCollisionBody(
		"baseCollsionBody",
		CollisionBodyType::HLine,
		{ baseWidth_, 0 },
		float4::RED,
		float4::BLACK,
		2
	);
	base_CollisionBody_->SetLocalPos({ 0, -56 });
	base_CollisionBody_->SetCameraEffectOn();
}

void Base::Update()
{
}

void Base::Render()
{
	base_Renderer_->Render();
	base_CollisionBody_->Render();
}

void Base::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
	if (CollisionBodyType::Rect == _otherCollisionBody->GetType() && "bird" == _other->GetName())
	{
		base_CollisionBody_->Respond();
	}
}
