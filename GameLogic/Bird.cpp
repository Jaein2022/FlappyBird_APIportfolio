#include "PreCompile.h"
#include "Bird.h"

Bird::Bird(): birdRenderer_(nullptr)
{
}

Bird::~Bird()
{
}

void Bird::Initialize()
{
	birdRenderer_ = CreateRenderer("bird.bmp", "birdRenderer");
	if (false == birdRenderer_->GetRenderingImage()->IsCut())
	{
		birdRenderer_->GetRenderingImage()->Cut({ 34, 24 });
	}
	birdRenderer_->CreateAnimation("Play", "bird.bmp", 0, 3, 0.1f);
	birdRenderer_->CreateAnimation("Ready", "bird.bmp", 0, 3, 0.5f);
	birdRenderer_->ChangeAnimation("Play");


	GameEngineInput::GetInst().CreateKey("W", 'W');
	GameEngineInput::GetInst().CreateKey("A", 'A');
	GameEngineInput::GetInst().CreateKey("S", 'S');
	GameEngineInput::GetInst().CreateKey("D", 'D');

	//GameEngineInput::GetInst().CreateKey("Space", ' ');
	//GameEngineInput::GetInst().CreateKey("Click", MK_LBUTTON);
		
}

void Bird::Update()
{
	//float4 thispos = this->GetPos();
	birdRenderer_->UpdateAnimation();
	float deltaTime = GameEngineTime::GetInst().GetDeltaTimeF();

	//임시 이동체계. 스우시, 콜리전 시스템 자리 잡히면 폐기.
	if (true == GameEngineInput::GetInst().IsPressed("W"))
	{
		Move(float4::DOWN * deltaTime * 100.f);
	}
	else if (true == GameEngineInput::GetInst().IsPressed("A"))
	{
		Move(float4::LEFT * deltaTime * 100.f);
	}
	else if (true == GameEngineInput::GetInst().IsPressed("S"))
	{
		Move(float4::UP * deltaTime * 100.f);
	}
	else if (true == GameEngineInput::GetInst().IsPressed("D"))
	{
		Move(float4::RIGHT * deltaTime * 100.f);
	}


}

void Bird::Render()
{
	//float4 rendererPos = birdRenderer_->GetLocalPos();
	birdRenderer_->Render();
}

void Bird::CheckCollision()
{
}
