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
	UI_(nullptr),
	allBackgrounds_(),
	backgroundWidth_(281),
	backgroundCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / backgroundWidth_) + 2),
	allBases_(),
	baseWidth_(336),
	baseCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / baseWidth_) + 2),
	allPipes_(),
	pipeStartPosX_(300),
	pipeInterval_(200),
	pipeCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / pipeInterval_) + 2)
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

	SetCameraPos(float4::ZERO);


	bird_ = CreateActor<Bird>("bird", 0, 8);
	bird_->SetWorldPos({ 50, 160 });

	UI_ = CreateActor<UI>("UI", 9, 9);
	UI_->SetWorldPos(GameEngineWindow::GetInst().GetWindowSize().Half());


	for (int i = 0; i < backgroundCount_; i++)
	{
		Background* newBackground = CreateActor<Background>("background" + std::to_string(i), 10, -1);
		newBackground->SetWorldPos({ backgroundWidth_ * i - (backgroundWidth_ / 2), 512 / 2 });
		allBackgrounds_.push_back(newBackground);
	}

	for (int i = 0; i < baseCount_; i++)
	{
		Base* newBase = CreateActor<Base>("base" + std::to_string(i), 1, 4);
		newBase->SetWorldPos({ baseWidth_ * i - (baseWidth_ / 2), 400 + 56 });
		allBases_.push_back(newBase);
	}

	for (int i = 0; i < pipeCount_; i++)
	{
		int pipeActorHeight = GameEngineRandom::GetInst().GetRandomInt(100, 325);
		Pipe* newPipe = CreateActor<Pipe>("pipe" + std::to_string(i), 2, 3);
		newPipe->SetWorldPos({ pipeInterval_ * i + pipeStartPosX_, pipeActorHeight });
		allPipes_.push_back(newPipe);
	}

}

void PlayLevel::UpdateLevel()
{
	for (Background* const background : allBackgrounds_)
	{
		if (background->GetCameraPos().IntX() < -(backgroundWidth_ / 2))
		{
			background->SetWorldPos(
				{ background->GetWorldPos().IntX() + backgroundWidth_ * backgroundCount_,
				512 / 2/*배경길이 절반*/});
		}
	}

	for (Base* const base : allBases_)
	{
		if (base->GetCameraPos().IntX() < -(baseWidth_ / 2))
		{
			base->SetWorldPos(
				{ base->GetWorldPos().IntX() + baseWidth_ * baseCount_,
				400 + 56/*원하는 배치높이 + 베이스높이 절반*/});
		}
	}	

	for (Pipe* const pipe : allPipes_)
	{
		if (pipe->GetCameraPos().IntX() < -(52 / 2))
		{
			pipe->SetWorldPos(
				{ pipe->GetWorldPos().IntX() + pipeInterval_ * pipeCount_,
				GameEngineRandom::GetInst().GetRandomInt(100, 325) });
			pipe->Relocate();
		}
	}
	




	if (true == GameEngineInput::GetInst().IsDown("M"))
	{
		this->SwitchMode();
	}

	if (true == GameEngineInput::GetInst().IsDown("Space"))
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
			currentState_ = GameState::Ready;
		}
	}
}

void PlayLevel::SwitchMode()
{
	GameEngineCollisionBody::SwitchRendering();

}
