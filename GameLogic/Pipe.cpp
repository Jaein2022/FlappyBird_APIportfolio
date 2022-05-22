#include "PreCompile.h"
#include "Pipe.h"

Pipe::Pipe()
	: pipeWidth_(52),
	pipeHeight_(320),
	pipeDistance_(84),
	topPipe_Renderer_(nullptr),
	topPipe_CollisionBody_(nullptr),
	botPipe_Renderer_(nullptr),
	botPipe_CollisionBody_(nullptr),
	scoreCount_CollsionBody_(nullptr)
{
}

Pipe::~Pipe()
{
}

void Pipe::Initialize()
{
	topPipe_Renderer_ = CreateRenderer("pipe_top.bmp", "topPipe_Renderer");
	topPipe_Renderer_->SetRenderingImagePivot(RenderPivot::Center);
	topPipe_Renderer_->SetLocalPos({ 0, -(pipeHeight_ + pipeDistance_) / 2 });

	topPipe_CollisionBody_ = CreateCollisionBody(
		"topPipe_CollisionBody",
		float4::RED,
		CollisionBodyType::Rect,
		{ pipeWidth_, pipeHeight_ }
	);
	topPipe_CollisionBody_->SetLocalPos({ 0, -(pipeHeight_ + pipeDistance_) / 2 });


	botPipe_Renderer_ = CreateRenderer("pipe_bot.bmp", "botPipe_Renderer");
	botPipe_Renderer_->SetRenderingImagePivot(RenderPivot::Center);
	botPipe_Renderer_->SetLocalPos({ 0, (pipeHeight_ + pipeDistance_) / 2 });

	botPipe_CollisionBody_ = CreateCollisionBody(
		"botPipe_CollisionBody",
		float4::RED,
		CollisionBodyType::Rect,
		{ pipeWidth_, pipeHeight_ }
	);
	botPipe_CollisionBody_->SetLocalPos({ 0, (pipeHeight_ + pipeDistance_) / 2 });


	scoreCount_CollsionBody_ = CreateCollisionBody(
		"scoreCount_CollsionBody",
		float4::YELLOW,
		CollisionBodyType::VLine,
		{ 0, GameEngineWindow::GetInst().GetWindowSize().IntY() * 2 }
	);
	scoreCount_CollsionBody_->SetLocalPos({ pipeWidth_ / 2 + 34, 0 });

}

void Pipe::Update()
{
}

void Pipe::Render()
{
	topPipe_Renderer_->Render();
	topPipe_CollisionBody_->Render();

	botPipe_Renderer_->Render();
	botPipe_CollisionBody_->Render();

	scoreCount_CollsionBody_->Render();
}

void Pipe::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
	if (_other->GetName() == "bird" && CollisionBodyType::Rect == _otherCollisionBody->GetType())
	{
		if (_thisCollisionBody == topPipe_CollisionBody_ )
		{
			topPipe_CollisionBody_->SetColor(float4::BLACK);
		}
		else if (_thisCollisionBody == botPipe_CollisionBody_)
		{
			botPipe_CollisionBody_->SetColor(float4::BLACK);
		}
		else if (_thisCollisionBody == scoreCount_CollsionBody_)
		{
			scoreCount_CollsionBody_->SetColor(float4::GREEN);
			scoreCount_CollsionBody_->SwitchUpdateInOut();
		}
	}
}
