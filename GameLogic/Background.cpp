#include "PreCompile.h"
#include "Background.h"

Background::Background(): rendererCount_(5), width_(281.00f), speed_(0.f)
{
	backgroundRenderers_.reserve(rendererCount_);
}

Background::~Background()
{
}

void Background::Initialize()
{
	for (int i = 0; i < rendererCount_; i++)
	{
		GameEngineRenderer* newRenderer = CreateRenderer(
			"background.bmp", "backgroundRenderer" + std::to_string(i));
		newRenderer->SetLocalPos({ static_cast<int>(width_) * i, 0 });
		backgroundRenderers_.push_back(newRenderer);
	}
}

void Background::Update()
{
	float deltaTime = GameEngineTime::GetInst().GetDeltaTimeF();
	for (GameEngineRenderer* renderer : backgroundRenderers_)
	{
		float rendererPosX = renderer->GetLocalPos().x;
		if (-(width_) >= rendererPosX)
		{
			renderer->SetLocalPos({ rendererPosX + width_ * static_cast<float>(rendererCount_), 0.f });
		}
		else
		{
			renderer->Move({ deltaTime * speed_ , 0.f });
		}
	}
}

void Background::Render()
{
	for ( GameEngineRenderer* renderer : backgroundRenderers_)
	{
		renderer->Render();
	}
}

void Background::CheckCollision()
{
}
