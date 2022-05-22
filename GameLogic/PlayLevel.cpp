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
	backgrounds_(),
	backgroundWidth_(281),
	backgroundCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / backgroundWidth_) + 2),
	bases_(),
	baseWidth_(336),
	baseCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / baseWidth_) + 2),
	pipes_(),
	pipeStartPosX_(300),
	pipeInterval_(200),
	pipeCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / pipeInterval_) + 2)
{
	backgrounds_.reserve(backgroundCount_);
	bases_.reserve(baseCount_);
	pipes_.reserve(pipeCount_);
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

	bird_ = CreateActor<Bird>("bird", 0, 8);
	bird_->SetWorldPos({ 100, 200 });

	UI_ = CreateActor<UI>("UI", 9, 9);
	UI_->SetWorldPos(GameEngineWindow::GetInst().GetWindowSize().Half());


	for (int i = 0; i < backgroundCount_; i++)
	{
		Background* newBackground = CreateActor<Background>("background" + std::to_string(i), 10, -1);
		newBackground->SetWorldPos({ backgroundWidth_ * i - (backgroundWidth_ / 2), 512 / 2 });
		backgrounds_.push_back(newBackground);
	}

	for (int i = 0; i < baseCount_; i++)
	{
		Base* newBase = CreateActor<Base>("base" + std::to_string(i), 1, 4);
		newBase->SetWorldPos({ baseWidth_ * i - (baseWidth_ / 2), 400 + 56 });
		bases_.push_back(newBase);
	}

	for (int i = 0; i < pipeCount_; i++)
	{
		int pipeActorHeight = GameEngineRandom::GetInst().GetRandomInt(100, 350);
		Pipe* newPipe = CreateActor<Pipe>("pipe" + std::to_string(i), 2, 3);
		newPipe->SetWorldPos({ pipeInterval_ * i + pipeStartPosX_, pipeActorHeight });
		pipes_.push_back(newPipe);
	}

}

void PlayLevel::UpdateLevel()
{
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
