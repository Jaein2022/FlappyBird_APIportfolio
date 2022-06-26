#include "PreCompile.h"
#include "Bird.h"
#include "Pipe.h"
#include "PlayLevel.h"


Bird::Bird()
	:birdSize_(34, 24),
	bird_Renderer_(nullptr),
	bird_CollisionBody_(nullptr),
	parentPlayLevel_(nullptr),
	initAscendingSpeed_(2.75f),
	fallingSpeed_(0.f),
	initAscendingSecond_(0.5f),
	ascendingSecond_(0.f),
	bird_SoundPlayer_(nullptr)
{
}

Bird::~Bird()
{
}

void Bird::Initialize()
{
	parentPlayLevel_ = dynamic_cast<PlayLevel*>(this->GetLevel());
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
	bird_Renderer_->CreateAnimation("Play", "bird.bmp", 0, 3, 0.075f);
	bird_Renderer_->CreateAnimation("Ready", "bird.bmp", 0, 3, 0.5f);
	bird_Renderer_->ChangeAnimation("Ready");
	bird_Renderer_->SetMaskImage("birdMask.bmp");

	bird_Renderer_->SetCameraEffectOn();


	
	bird_CollisionBody_ = CreateCollisionBody(
		"bird_CollisionBody",
		CollisionBodyType::RRect,
		birdSize_,
		float4::Red,
		float4::Black,
		2
	);
	bird_CollisionBody_->SetCameraEffectOn();


	bird_SoundPlayer_ = GameEngineSoundManager::GetInst().CreateSoundPlayer("wing_SoundPlayer");
}

void Bird::Update()
{
	bird_Renderer_->UpdateAnimation();

	if (true == GameEngineInput::GetInst().IsDown("Space"))
	{
		fallingSpeed_ = -initAscendingSpeed_;
		ascendingSecond_ = initAscendingSecond_;
		bird_SoundPlayer_->PlayOverLap("wing.wav", 0);
	}

	SetAngle(GameEngineTime::GetInst().GetDeltaTimeF());

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
	if (CollisionBodyType::HLine == _otherCollisionBody->GetType() &&
		std::string::npos != _other->GetName().find("base"))
	{
		parentPlayLevel_->SetState(GameState::GameOver);
		bird_CollisionBody_->Respond(true);
		_otherCollisionBody->Respond(true);
		bird_SoundPlayer_->PlayOverLap("die.wav", 0);
	}

	if (std::string::npos != _other->GetName().find("pipe"))
	{
		_otherCollisionBody->Respond(true);

		if (CollisionBodyType::FRect == _otherCollisionBody->GetType())
		{
			parentPlayLevel_->SetState(GameState::GameOver);
			bird_CollisionBody_->Respond(true);
			bird_SoundPlayer_->PlayOverLap("hit.wav", 0);
		}
		else if (CollisionBodyType::VLine == _otherCollisionBody->GetType())
		{
			parentPlayLevel_->AddScore();
			bird_SoundPlayer_->PlayOverLap("point.wav", 0);
		}
	}
}

void Bird::ControlMoving(float _deltaTime, const float _gravity, const float _playSpeed)
{
	if (false == parentPlayLevel_->IsDebuging())
	{
		switch (parentPlayLevel_->GetState())
		{
		case GameState::Ready:
		{
			fallingSpeed_ = -initAscendingSpeed_;
			bird_Renderer_->SetAngle(0.f);
			bird_CollisionBody_->SetRrectAngle(0.f);
			if ("Ready" != bird_Renderer_->GetCurAnimationName())
			{
				bird_Renderer_->ChangeAnimation("Ready", true);

				bird_SoundPlayer_->PlayOverLap("swoosh.wav", 0);
			}
			break;
		}

		case GameState::Playing:
		{
			if ("Play" != bird_Renderer_->GetCurAnimationName())
			{
				bird_Renderer_->ChangeAnimation("Play", true);
				bird_SoundPlayer_->PlayOverLap("wing.wav", 0);
			}

			//연직 상방운동중인 물체의 속도 = 처음 발사된 속도 - 중력가속도 * 발사된 시점에서부터 지난 시간.
			fallingSpeed_ += _gravity * _deltaTime;

			Move(float4::Down * _deltaTime * _playSpeed * fallingSpeed_);
			Move(float4::Right * _deltaTime * _playSpeed);
			break;
		}

		case GameState::GameOver:
		{
			if (400.f - birdSize_.Half_Y() > this->GetWorldPos().y)
			{
				fallingSpeed_ += _gravity * _deltaTime;
				Move(float4::Down * _deltaTime * _playSpeed * fallingSpeed_);
			}
			else
			{
				SetWorldPos({ this->GetWorldPos().x, 400.f - birdSize_.Half_Y()});
				bird_Renderer_->SetFrameIndex(2, RenderPivot::Center);
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
		else if (true == GameEngineInput::GetInst().IsPressed("Q"))
		{
			bird_Renderer_->Rotate(360.f * _deltaTime);
			bird_CollisionBody_->RotateRrect(360.f * _deltaTime);
		}	
		else if (true == GameEngineInput::GetInst().IsPressed("E"))
		{
			bird_Renderer_->Rotate(-360.f * _deltaTime);
			bird_CollisionBody_->RotateRrect(-360.f * _deltaTime);
		}
	}
}

void Bird::SetAngle(float _deltaTime)
{
	if (true == parentPlayLevel_->IsDebuging())
	{
		return;
	}

	if (0.f <= ascendingSecond_)
	{
		ascendingSecond_ -= _deltaTime;
		bird_Renderer_->SetAngle(-20.f);
		bird_CollisionBody_->SetRrectAngle(-20.f);
	}
	else
	{
		if (0.5f > fallingSpeed_)
		{
			bird_Renderer_->SetAngle(0.f);
			bird_CollisionBody_->SetRrectAngle(0.f);
		}
		else if (0.5f <= fallingSpeed_ && 0.6f > fallingSpeed_)
		{
			bird_Renderer_->SetAngle(20.f);
			bird_CollisionBody_->SetRrectAngle(20.f);
		}
		else if (0.6f <= fallingSpeed_)
		{
			bird_Renderer_->SetAngle(70.f);
			bird_CollisionBody_->SetRrectAngle(70.f);
		}
	}
}
