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
	baseCollisionBody_ = CreateCollisionBody("baseCollsionBody", float4::RED, CollisionBodyType::HLine);
	baseCollisionBody_->SetSize({ baseWidth_, 0 });



}

void Base::Update()
{
}

void Base::Render()
{
	baseRenderer_->Render();
	baseCollisionBody_->Render();
}

void Base::ReactCollision()
{
}
