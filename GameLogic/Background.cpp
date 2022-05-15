#include "PreCompile.h"
#include "Background.h"

Background::Background(): backgroundRenderer_(nullptr)
{

}

Background::~Background()
{
}

void Background::Initialize()
{
	backgroundRenderer_ = CreateRenderer("background.bmp", "backgroundRenderer");
	//backgroundRenderer_->SetCameraEffectOn();
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
	backgroundRenderer_->Render();
}

void Background::CheckCollision()
{
}
