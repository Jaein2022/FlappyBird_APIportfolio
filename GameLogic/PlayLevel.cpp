#include "PreCompile.h"
#include "PlayLevel.h"
#include "Background.h"
#include "Bird.h"
#include "Pipe.h"
#include "UI.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Load()
{
	CreateActor<Background>("Background", 10, 0);
}
