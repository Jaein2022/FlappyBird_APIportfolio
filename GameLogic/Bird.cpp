#include "PreCompile.h"
#include "Bird.h"
#include "Pipe.h"
#include "PlayLevel.h"

Bird::Bird(): bird_Renderer_(nullptr), bird_CollisionBody_(nullptr)
{
}

Bird::~Bird()
{
}

void Bird::Initialize()
{
	bird_Renderer_ = CreateRenderer("bird.bmp", "bird_Renderer");
	if (false == bird_Renderer_->GetRenderingImage()->IsCut())
	{
		bird_Renderer_->GetRenderingImage()->Cut({ 34, 24 });
	}
	bird_Renderer_->CreateAnimation("Play", "bird.bmp", 0, 3, 0.1f);
	bird_Renderer_->CreateAnimation("Ready", "bird.bmp", 0, 3, 0.5f);
	bird_Renderer_->ChangeAnimation("Play");


	//birdRenderer_->SetCameraEffectOn();


	
	bird_CollisionBody_ = CreateCollisionBody(
		"birdCollisionBody", float4::RED, CollisionBodyType::Rect, { 34, 24 });

}

void Bird::Update()
{
	//float4 thispos = this->GetPos();
	bird_Renderer_->UpdateAnimation();
	float deltaTime = GameEngineTime::GetInst().GetDeltaTimeF();

	//충돌테스트용 임시 이동체계.
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
	bird_Renderer_->Render();
	bird_CollisionBody_->Render();
}

void Bird::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
	if (CollisionBodyType::Rect == _otherCollisionBody->GetType() ||
		CollisionBodyType::HLine == _otherCollisionBody->GetType())
	{
		bird_CollisionBody_->SetColor(float4::BLACK);
		PlayLevel* tempPlayLevel = reinterpret_cast<PlayLevel*>(this->GetLevel());
		tempPlayLevel->SetState(GameState::GameOver);
	}
}
