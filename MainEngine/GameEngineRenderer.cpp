#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineImage.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Render()
{
}

void GameEngineRenderer::SetActorImagePivot(RenderPivot _pivot)
{
	switch (_pivot)
	{
	case RenderPivot::CENTER:
		actorImagePivot_ = actorImage_->GetSize().Half();
		break;
	case RenderPivot::BOT:
		actorImagePivot_ = actorImage_->GetSize().Half();
		actorImagePivot_.y_ = actorImage_->GetSize().y_;
		break;
	case RenderPivot::LEFTTOP:
		actorImagePivot_ = float4::ZERO;
		break;

	default:
		GameEngineDebug::MsgBoxError("지정할 수 없는 방식의 이미지 피봇입니다.");
		break;
	}
}

void GameEngineRenderer::CreateAnimation(const std::string& _animationName, const std::string& _imageName, int _startIndex, int _finishIndex, float _delayPerFrame, bool isRepetitive_, RenderPivot _pivot)
{
}
