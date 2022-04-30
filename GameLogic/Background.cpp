#include "PreCompile.h"
#include "Background.h"

Background::Background(): rendererCount_(6), widthInt_(281), widthFloat_(281.00f), backgroundSpeed_(-150.f)
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
			"background_day.bmp", "background_day_renderer" + std::to_string(i));
		newRenderer->SetLocalPos({ (widthInt_ * i), 0 });
		backgroundRenderers_.push_back(newRenderer);
	}
}

void Background::Update()
{
	float deltaTime = GameEngineTime::GetInst().GetDeltaTimeF();
	for (GameEngineRenderer* renderer : backgroundRenderers_)
	{
		float rendererPos = renderer->GetLocalPos().x_;
		if (-(widthFloat_) >= rendererPos)
		{
			renderer->SetLocalPos({ rendererPos + widthFloat_ * static_cast<float>(rendererCount_), 0.f });
		}
		else
		{
			renderer->Move({ deltaTime * backgroundSpeed_ , 0.f });
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
