#include "PreCompile.h"
#include "Pipe.h"
#include "PlayLevel.h"

Pipe::Pipe()
	: pipeSize_(52, 320),
	pipeDistance_(84 /*84*/),
	topPipe_Renderer_(nullptr),
	topPipe_CollisionBody_(nullptr),
	botPipe_Renderer_(nullptr),
	botPipe_CollisionBody_(nullptr),
	scoreCount_CollsionBody_(nullptr),
	score_SoundPlayer_(nullptr)
{
}

Pipe::~Pipe()
{
}

void Pipe::Initialize()
{
	topPipe_Renderer_ = CreateRenderer("pipe_top.bmp", "topPipe_Renderer");
	topPipe_Renderer_->SetRenderPivot(RenderPivot::Center);
	topPipe_Renderer_->SetLocalPos({ 0, -(pipeSize_.IntY() + pipeDistance_) / 2});
	topPipe_Renderer_->SetCameraEffectOn();

	topPipe_CollisionBody_ = CreateCollisionBody(
		"topPipe_CollisionBody",
		CollisionBodyType::FRect,
		pipeSize_,
		float4::Red,
		float4::Black,
		2
	);
	topPipe_CollisionBody_->SetLocalPos({ 0, -(pipeSize_.IntY() + pipeDistance_) / 2});
	topPipe_CollisionBody_->SetCameraEffectOn();



	botPipe_Renderer_ = CreateRenderer("pipe_bot.bmp", "botPipe_Renderer");
	botPipe_Renderer_->SetRenderPivot(RenderPivot::Center);
	botPipe_Renderer_->SetLocalPos({ 0, (pipeSize_.IntY() + pipeDistance_) / 2 });
	botPipe_Renderer_->SetCameraEffectOn();

	botPipe_CollisionBody_ = CreateCollisionBody(
		"botPipe_CollisionBody",
		CollisionBodyType::FRect,
		pipeSize_,
		float4::Red,
		float4::Black,
		2
	);
	botPipe_CollisionBody_->SetLocalPos({ 0, (pipeSize_.IntY() + pipeDistance_) / 2 });
	botPipe_CollisionBody_->SetCameraEffectOn();

	scoreCount_CollsionBody_ = CreateCollisionBody(
		"scoreCount_CollsionBody",
		CollisionBodyType::VLine,
		{ 0, GameEngineWindow::GetInst().GetWindowSize().IntY() * 2 },
		float4::Yellow,
		float4::Green,
		2
	);
	scoreCount_CollsionBody_->SetLocalPos({ pipeSize_.Half_IntX() + 34, 0});
	scoreCount_CollsionBody_->SetCameraEffectOn();

	score_SoundPlayer_ = GameEngineSoundManager::GetInst().CreateSoundPlayer("score_SoundPlayer");
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
}
