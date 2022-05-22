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


	base_CollisionBody_ = CreateCollisionBody(
		"baseCollsionBody",
		float4::RED,
		CollisionBodyType::HLine,
		{ baseWidth_, 0 }
	);
	base_CollisionBody_->SetLocalPos({ 0, -56 });



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
	if (_other->GetName() == "bird" && CollisionBodyType::Rect == _otherCollisionBody->GetType())
	{
		base_CollisionBody_->SetColor(float4::BLACK);
	}
}
