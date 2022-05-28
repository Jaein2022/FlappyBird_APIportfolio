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
	//float deltaTime = GameEngineTime::GetInst().GetDeltaTimeF();
	//for (GameEngineRenderer* renderer : backgroundRenderers_)
	//{
	//	float rendererPosX = renderer->GetLocalPos().x;
	//	if (-(width_) >= rendererPosX)
	//	{
	//		renderer->SetLocalPos({ rendererPosX + width_ * static_cast<float>(rendererCount_), 0.f });
	//	}
	//	else
	//	{
	//		renderer->Move({ deltaTime * speed_ , 0.f });
	//	}
	//}


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
