#include "PreCompile.h"
#include "PlayLevel.h"
#include "Background.h"
#include "Bird.h"
#include "Pipe.h"
#include "Base.h"
#include "UI.h"
#include <Basement\GameEngineRandom.h>

PlayLevel::PlayLevel()
	: score_(0),
	currentState_(GameState::Ready),
	bird_(nullptr),
	birdStartPos_(50, 160),
	UI_(nullptr),
	allBackgrounds_(),
	backgroundSize_(281, 512),
	backgroundCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / backgroundSize_.IntY()) + 2),
	allBases_(),
	baseSize_(336, 112),
	basePosY_(400 + baseSize_.Half_IntY()),
	baseCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / baseSize_.IntX()) + 2),
	allPipes_(),
	pipeStartPosX_(300),
	pipeInterval_(200),
	pipeCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / pipeInterval_) + 2),
	isDebuging_(false),
	playSpeed_(100.f),
	gravity_(9.80665f)
{
	allBackgrounds_.reserve(backgroundCount_);
	allBases_.reserve(baseCount_);
	allPipes_.reserve(pipeCount_);
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Load()
{
	GameEngineInput::GetInst().CreateKey("W", 'W');
	GameEngineInput::GetInst().CreateKey("A", 'A');
	GameEngineInput::GetInst().CreateKey("S", 'S');
	GameEngineInput::GetInst().CreateKey("D", 'D');

	GameEngineInput::GetInst().CreateKey("M", 'M');

	GameEngineInput::GetInst().CreateKey("Space", ' ');

	SetCameraPos(float4::Zero);


	bird_ = CreateActor<Bird>("bird", 0, 8);
	bird_->SetWorldPos(birdStartPos_);

	UI_ = CreateActor<UI>("UI", 9, 9);
	UI_->SetWorldPos(GameEngineWindow::GetInst().GetWindowSize().Half());



	for (int i = 0; i < backgroundCount_; i++)
	{
		Background* newBackground = CreateActor<Background>(
			"background" + std::to_string(i),
			10,
			-1
			);
		newBackground->SetWorldPos(
			{ backgroundSize_.IntX() * i - backgroundSize_.Half_IntX(), backgroundSize_.Half_IntY()});
		allBackgrounds_.push_back(newBackground);
	}

	for (int i = 0; i < baseCount_; i++)
	{
		Base* newBase = CreateActor<Base>(
			"base" + std::to_string(i),
			1,
			4);
		newBase->SetWorldPos(
			{ baseSize_.IntX() * i - baseSize_.Half_IntX(), basePosY_});
		allBases_.push_back(newBase);
	}

	for (int i = 0; i < pipeCount_; i++)
	{
		int pipeActorHeight = GameEngineRandom::GetInst().GetRandomInt(100, 325);
		Pipe* newPipe = CreateActor<Pipe>(
			"pipe" + std::to_string(i),
			2,
			3);
		newPipe->SetWorldPos(
			{ pipeInterval_ * i + pipeStartPosX_, pipeActorHeight });
		allPipes_.push_back(newPipe);
	}

}

void PlayLevel::UpdateLevel()
{
	SetCameraPos({bird_->GetWorldPos().IntX() - birdStartPos_.IntX(), 0});

	for (Background* const background : allBackgrounds_)
	{
		if (background->GetCameraPos().IntX() < -backgroundSize_.Half_IntX())
		{
			background->SetWorldPos(
				{ background->GetWorldPos().IntX() + backgroundSize_.IntX() * backgroundCount_,
				backgroundSize_.Half_IntY() }
			);
		}
	}

	for (Base* const base : allBases_)
	{
		if (base->GetCameraPos().IntX() < -baseSize_.Half_IntX())
		{
			base->SetWorldPos(
				{ base->GetWorldPos().IntX() + baseSize_.IntX() * baseCount_,
				basePosY_ }
			);
			base->ResetCollisionBodies();
		}
	}	

	for (Pipe* const pipe : allPipes_)
	{
		if (pipe->GetCameraPos().IntX() < -(pipeInterval_ / 2))
		{
			pipe->SetWorldPos(
				{ pipe->GetWorldPos().IntX() + pipeInterval_ * pipeCount_,
				GameEngineRandom::GetInst().GetRandomInt(100, 325) }
			);
			pipe->ResetCollisionBodies();
		}
	}

	if (true == GameEngineInput::GetInst().IsDown("M"))
	{
		this->SwitchMode();
	}

	if (true == GameEngineInput::GetInst().IsUp("Space"))
	{
		if (GameState::Ready == currentState_) 
		{
			currentState_ = GameState::Playing;
		}			
		else if (GameState::Playing == currentState_)
		{
			
		}
		else if (GameState::GameOver == currentState_)
		{
			Reset();
			currentState_ = GameState::Ready;
		}
	}
}

void PlayLevel::SwitchMode()
{
	GameEngineCollisionBody::SwitchRendering();
	isDebuging_ = !isDebuging_;
}

void PlayLevel::Reset()
{
	GameEngineTime::GetInst().Reset();
	SetCameraPos(float4::Zero);
	bird_->SetWorldPos(birdStartPos_);
	bird_->ResetCollisionBodies();
	UI_->SetWorldPos(GameEngineWindow::GetInst().GetWindowSize().Half());
	score_ = 0;
	GameEngineRandom::GetInst().Renewal();
	

	for (int i = 0; i < backgroundCount_; i++)
	{
		allBackgrounds_[i]->SetWorldPos(
			{ backgroundSize_.IntX() * i - backgroundSize_.Half_IntX(), backgroundSize_.Half_IntY()});
	}

	for (int i = 0; i < baseCount_; i++)
	{
		allBases_[i]->SetWorldPos(
			{baseSize_.IntX() * i - baseSize_.Half_IntX(), basePosY_});
		allBases_[i]->ResetCollisionBodies();
	}

	for (int i = 0; i < pipeCount_; i++)
	{
		int pipeActorHeight = GameEngineRandom::GetInst().GetRandomInt(100, 325);
		allPipes_[i]->SetWorldPos({ pipeInterval_ * i + pipeStartPosX_, pipeActorHeight });
		allPipes_[i]->ResetCollisionBodies();
	}


}
