#include "PreCompile.h"
#include "UI.h"
#include "PlayLevel.h"
#include "LogicEnum.h"

UI::UI()
	: parentPlayLevel_(nullptr),
	readyMessage_Renderer_(nullptr),
	score_FirstDigit_Renderer_(nullptr),
	score_SecondDigit_Renderer_(nullptr),
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

	score_FirstDigit_Renderer_ = CreateRenderer("number.bmp", "score_FirstDigit_Renderer");
	if (false == score_FirstDigit_Renderer_->GetRenderingImage()->IsCut())
	{
		score_FirstDigit_Renderer_->GetRenderingImage()->Cut({24, 36});
	}
		
	score_SecondDigit_Renderer_ = CreateRenderer("number.bmp", "score_SecondDigit_Renderer");
	score_SecondDigit_Renderer_->SetLocalPos({ 0, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });


	gameover_Renderer_ = CreateRenderer("gameover.bmp", "gameover_Renderer");
	gameover_Renderer_->SetRenderPivot(RenderPivot::Center);
	gameover_Renderer_->SetLocalPos({ 0, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 90 + 21 });

}

void UI::Update()
{
	if (GameState::Playing == parentPlayLevel_->GetState() ||
		GameState::GameOver == parentPlayLevel_->GetState())
	{
		int currentScore = parentPlayLevel_->GetScore();

		if (currentScore < 10)
		{
			score_FirstDigit_Renderer_->SetLocalPos(
				{ 0, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });

			score_FirstDigit_Renderer_->SetFrameIndex(
				currentScore,
				RenderPivot::Center
			);
		}
		else if (currentScore >= 10 && currentScore < 100)
		{
			score_FirstDigit_Renderer_->SetLocalPos(
				{ 12, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });
			score_SecondDigit_Renderer_->SetLocalPos(
				{ -12, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });

			score_FirstDigit_Renderer_->SetFrameIndex(
				currentScore % 10,
				RenderPivot::Center
			);
			score_SecondDigit_Renderer_->SetFrameIndex(
				currentScore / 10,
				RenderPivot::Center
			);

		}
		else
		{
			score_FirstDigit_Renderer_->SetLocalPos(
				{ 12, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });
			score_SecondDigit_Renderer_->SetLocalPos(
				{ -12, -GameEngineWindow::GetInst().GetWindowSize().Half_IntY() + 40 + 18 });

			score_FirstDigit_Renderer_->SetFrameIndex(9, RenderPivot::Center);
			score_SecondDigit_Renderer_->SetFrameIndex(9, RenderPivot::Center);
		}



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
	{
		if (parentPlayLevel_->GetScore() < 10)
		{
			score_FirstDigit_Renderer_->Render();
		}
		else if(parentPlayLevel_->GetScore() >= 10)
		{
			score_FirstDigit_Renderer_->Render();
			score_SecondDigit_Renderer_->Render();
		}
		break;
	}
	case GameState::GameOver:
	{
		gameover_Renderer_->Render();

		if (parentPlayLevel_->GetScore() < 10)
		{
			score_FirstDigit_Renderer_->Render();
		}
		else if (parentPlayLevel_->GetScore() >= 10)
		{
			score_FirstDigit_Renderer_->Render();
			score_SecondDigit_Renderer_->Render();
		}
		break;
	}

	default:
		GameEngineDebug::MsgBoxError("존재할 수 없는 게임 스테이트입니다.");
		return;
	}
}

void UI::ReactCollision(
	GameEngineCollisionBody* _thisCollisionBody,
	GameEngineActor* _other,
	GameEngineCollisionBody* _otherCollisionBody
)
{
}
