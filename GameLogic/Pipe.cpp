#include "PreCompile.h"
#include "Pipe.h"

Pipe::Pipe()
	: pipeWidth_(52),
	pipeHeight_(320),
	pipeDistance_(0),
	topPipe_Renderer_(nullptr),
	topPipe_CollisionBody_(nullptr),
	botPipe_Renderer_(nullptr),
	botPipe_CollisionBody_(nullptr)
{
}

Pipe::~Pipe()
{
}

void Pipe::Initialize()
{
	topPipe_Renderer_ = CreateRenderer("pipe_top.bmp", "topPipe_Renderer");
	




	botPipe_Renderer_ = CreateRenderer("pipe_bot.bmp", "botPipe_Renderer");
}

void Pipe::Update()
{
}

void Pipe::Render()
{

}

void Pipe::ReactCollision()
{
}
