#include "PreCompile.h"
#include "Bird.h"

Bird::Bird(): birdRenderer_(nullptr), birdCollisionBody_(nullptr)
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
	birdRenderer_->SetCameraEffectOn();


	GameEngineInput::GetInst().CreateKey("W", 'W');
	GameEngineInput::GetInst().CreateKey("A", 'A');
	GameEngineInput::GetInst().CreateKey("S", 'S');
	GameEngineInput::GetInst().CreateKey("D", 'D');

	//GameEngineInput::GetInst().CreateKey("Space", ' ');
	//GameEngineInput::GetInst().CreateKey("Click", MK_LBUTTON);
	
	birdCollisionBody_ = CreateCollisionBody("birdCollisionBody", float4::RED, CollisionBodyType::Rect);
	birdCollisionBody_->SetSize({ 34, 24 });


}

void Bird::Update()
{
	//float4 thispos = this->GetPos();
	birdRenderer_->UpdateAnimation();
	float deltaTime = GameEngineTime::GetInst().GetDeltaTimeF();

	//임시 이동체계.
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

	//birdCollisionBody_->CheckCollision();


}

void Bird::Render()
{
	birdRenderer_->Render();
	birdCollisionBody_->Render();
}

void Bird::ReactCollision()
{
	int i = 0;
}
