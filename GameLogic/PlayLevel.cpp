#include "PreCompile.h"
#include "PlayLevel.h"
#include "Background.h"
#include "Bird.h"
#include "Base.h"
#include "UI.h"

PlayLevel::PlayLevel() 
	: bird_(nullptr),
	backgrounds_(),
	backgroundWidth_(281),
	backgroundCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / backgroundWidth_) + 2),
	bases_(),
	baseWidth_(336),
	baseCount_((GameEngineWindow::GetInst().GetWindowSize().IntX() / baseWidth_) + 2)
{
	backgrounds_.reserve(backgroundCount_);
	bases_.reserve(baseCount_);
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Load()
{

	bird_ = CreateActor<Bird>("bird", 0, 9);
	bird_->SetWorldPos({ 100, 100 });


	for (int i = 0; i < backgroundCount_; i++)
	{
		Background* newBackground = CreateActor<Background>("background" + std::to_string(i), 10, -1);
		newBackground->SetWorldPos({ backgroundWidth_ * i - backgroundWidth_, 0 });
		backgrounds_.push_back(newBackground);
	}

	for (int i = 0; i < baseCount_; i++)
	{
		Base* newBase = CreateActor<Base>("base" + std::to_string(i), 1, 4);
		newBase->SetWorldPos({ baseWidth_ * i - baseWidth_, 400 });
		bases_.push_back(newBase);
	}


}

void PlayLevel::UpdateLevel()
{
}
