#include "PreCompile.h"
#include "Background.h"

Background::Background(): background_Renderer_(nullptr)
{

}

Background::~Background()
{
}

void Background::Initialize()
{
	background_Renderer_ = CreateRenderer("background.bmp", "background_Renderer");
	background_Renderer_->SetRenderPivot(RenderPivot::Center);
	background_Renderer_->SetCameraEffectOn();
}

void Background::Update()
{
}

void Background::Render()
{
	background_Renderer_->Render();
}

void Background::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
}
