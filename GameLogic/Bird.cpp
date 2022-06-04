#include "PreCompile.h"
#include "Bird.h"
#include "Pipe.h"
#include "PlayLevel.h"

Bird::Bird()
	:birdSize_( 34, 24 ),
	bird_Renderer_(nullptr),
	bird_CollisionBody_(nullptr), 
	parentPlayLevel_(nullptr),
	initAscendingSpeed_(2.75f),	/*20.82f*/
	fallingSpeed_(0.f)
{
}

Bird::~Bird()
{
}

void Bird::Initialize()
{
	parentPlayLevel_ = reinterpret_cast<PlayLevel*>(this->GetLevel());
	if (nullptr == parentPlayLevel_)
	{
		GameEngineDebug::MsgBoxError("parentPlayLevel이 없습니다.");
		return;
	}


	if(false == GameEngineImageManager::GetInst().Find("bird.bmp")->IsCut())
	{
		GameEngineImageManager::GetInst().Find("bird.bmp")->Cut(birdSize_);
	}
	bird_Renderer_ = CreateRenderer("bird.bmp", "bird_Renderer");
	bird_Renderer_->CreateAnimation("Play", "bird.bmp", 0, 3, 0.1f);
	bird_Renderer_->CreateAnimation("Ready", "bird.bmp", 0, 3, 0.5f);
	bird_Renderer_->ChangeAnimation("Play");


	bird_Renderer_->SetCameraEffectOn();


	
	bird_CollisionBody_ = CreateCollisionBody(
		"birdCollisionBody",
		CollisionBodyType::Rect,
		{ birdSize_.IntX() - 2, birdSize_.IntY() - 2 },
		float4::Red,
		float4::Black,
		2
	);
	bird_CollisionBody_->SetCameraEffectOn();
}

void Bird::Update()
{
	bird_Renderer_->UpdateAnimation();


	ControlMoving(
		GameEngineTime::GetInst().GetDeltaTimeF(),
		parentPlayLevel_->GetGravity(),
		parentPlayLevel_->GetPlaySpeed()
	);





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
		bird_CollisionBody_->Respond();

		parentPlayLevel_->SetState(GameState::GameOver);
	}
}

void Bird::ControlMoving(float _deltaTime, const float _gravity, const float _playSpeed)
{
	if (false == parentPlayLevel_->IsDebuging())
	{
		switch (parentPlayLevel_->GetState())
		{
		case GameState::Ready:
			fallingSpeed_ = 0.f;
			break;

		case GameState::Playing:
		{
			if (true == GameEngineInput::GetInst().IsDown("Space"))
			{
				fallingSpeed_ = -initAscendingSpeed_;
			}

			fallingSpeed_ += _gravity * _deltaTime;

			Move(float4::Down * _deltaTime * _playSpeed * fallingSpeed_);
			Move(float4::Right * _deltaTime * _playSpeed);
			break;
		}

		case GameState::GameOver:
		{
			if (400 > this->GetWorldPos().IntY())
			{
				fallingSpeed_ += _gravity * _deltaTime;
				Move(float4::Down * _deltaTime * _playSpeed * fallingSpeed_);
			}
			else
			{
				SetWorldPos({ this->GetWorldPos().x, 400.f });
			}
			break;
		}


		default:
			GameEngineDebug::MsgBoxError("존재하지 않는 게임스테이트입니다.");
			return;
		}
	}
	else
	{
		//디버깅용 이동체계.
		if (true == GameEngineInput::GetInst().IsPressed("W"))
		{
			Move(float4::Up * _deltaTime * _playSpeed);
		}
		else if (true == GameEngineInput::GetInst().IsPressed("A"))
		{
			Move(float4::Left * _deltaTime * _playSpeed);
		}
		else if (true == GameEngineInput::GetInst().IsPressed("S"))
		{
			Move(float4::Down * _deltaTime * _playSpeed);
		}
		else if (true == GameEngineInput::GetInst().IsPressed("D"))
		{
			Move(float4::Right * _deltaTime * _playSpeed);
		}
	}
}
