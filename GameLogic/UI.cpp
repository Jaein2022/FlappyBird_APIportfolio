#include "PreCompile.h"
#include "UI.h"
#include "PlayLevel.h"
#include "LogicEnum.h"

UI::UI()
	: parentPlayLevel_(nullptr),
	readyMessage_Renderer_(nullptr),
	score_Renderer_(nullptr),
	gameover_Renderer_(nullptr)
{
}

UI::~UI()
{
}

void UI::Initialize()
{
	parentPlayLevel_ = reinterpret_cast<PlayLevel*>(this->GetLevel());

	readyMessage_Renderer_ = CreateRenderer("message.bmp", "readyMessage_Renderer");
	readyMessage_Renderer_->SetRenderPivot(RenderPivot::Bottom);	//이 게임에서 유일하게 얘만 렌더피봇이 바닥.

	score_Renderer_ = CreateRenderer("number.bmp", "score_Renderer");
	if (false == score_Renderer_->GetRenderingImage()->IsCut())
	{
		score_Renderer_->GetRenderingImage()->Cut({24, 36});
	}
	score_Renderer_->SetLocalPos({ 0, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });


	gameover_Renderer_ = CreateRenderer("gameover.bmp", "gameover_Renderer");
	gameover_Renderer_->SetRenderPivot(RenderPivot::Center);
	gameover_Renderer_->SetLocalPos({ 0, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 90 + 21 });

}

void UI::Update()
{
	if (GameState::Playing == parentPlayLevel_->GetState() ||
		GameState::GameOver == parentPlayLevel_->GetState())
	{
		score_Renderer_->SetFrameIndex(
			parentPlayLevel_->GetScore(),
			RenderPivot::Center
		);
	}
}

void UI::Render()
{
	switch (parentPlayLevel_->GetState())
	{
	case GameState::Ready:
		readyMessage_Renderer_->Render();
		break;
	case GameState::Playing:
		score_Renderer_->Render();
		break;
	case GameState::GameOver:
		score_Renderer_->Render();
		gameover_Renderer_->Render();
		break;

	default:
		GameEngineDebug::MsgBoxError("존재할 수 없는 게임 스테이트입니다.");
		break;
	}
}

void UI::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
}
