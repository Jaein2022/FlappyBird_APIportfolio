#include "PreCompile.h"
#include "PlayLevel.h"
#include "Background.h"
#include "Bird.h"
#include "Pipe.h"
#include "UI.h"

PlayLevel::PlayLevel() : playSpeed_(150.00f), bird_(nullptr), background_(nullptr)
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Load()
{
	background_ = CreateActor<Background>("Background", 10, 0);
	background_->SetSpeed(playSpeed_ * -0.50f);

	bird_ = CreateActor<Bird>("Bird", 0, 9);
	bird_->SetPos({ 100, 100 });




}
