#include "PreCompile.h"
#include "Background.h"

Background::Background(): background_Renderer_(nullptr)
{
}

Background::~Background()
{
}

void Background::Initialize()
{
	background_Renderer_ = CreateRenderer("background_day.bmp", "background_day_Renderer");
}

void Background::Update()
{
}

void Background::Render()
{
	background_Renderer_->Render();
}
