#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"

void GameEngineRenderer::Animation::Update()
{
	isFinished_ = false;

	curDelay_ -= GameEngineTime::GetInst().GetDeltaTimeF();
	if (0.0f >= curDelay_)
	{
		++curIndex_;
		if (finishIndex_ < curIndex_)
		{
			isFinished_ = true;
			if (true == isRepetitive_)
			{
				curIndex_ = startIndex_;
			}
			else
			{
				--curIndex_;
			}
		}
		curDelay_ = delayPerFrame_;
	}
	//parentRenderer_->SetFrameIndex(curIndex_, pivot_);
	//parentRenderer_->Render();
}


GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetActorImage(const std::string& _imageName)
{
	actorImage_ = GameEngineImageManager::GetInst().Find(_imageName);
	if (nullptr == actorImage_)
	{
		GameEngineDebug::MsgBoxError(_imageName + ": �׷� �̸��� �̹����� �����ϴ�.");
		return;
	}

	renderSize_ = actorImage_->GetSize();
	actorImageSize_ = actorImage_->GetSize();
}

void GameEngineRenderer::SetMaskImage(const std::string& _maskName)
{
	maskImage_ = GameEngineImageManager::GetInst().Find(_maskName);
	if (nullptr == maskImage_)
	{
		GameEngineDebug::MsgBoxError(_maskName + ": �׷� �̸��� ����ũ�� �����ϴ�.");
		return;
	}
}

void GameEngineRenderer::Render()
{
	GameEngineImage* backBufferImage = GameEngineImageManager::GetInst().GetBackBufferImage();

	if (nullptr == backBufferImage)
	{
		GameEngineDebug::MsgBoxError("����� �̹����� �����ϴ�.");
		return;
	}

	float4 renderPos = float4(0, 0);
	//ī�޶� ü�� ������ �Ʒ� �ڵ� �߰�.
	//if (true == isCameraEffect_)
	//{
	//	renderPos = GetParent()->GetCameraPos() + pivotPos_ - actorImagePivot_;
	//}
	//else
	//{
	//	renderPos = GetParent()->GetActorPos() + pivotPos_ - actorImagePivot_;
	//}

	backBufferImage->BitCopy(actorImage_, actorImagePos_, actorImageSize_, renderPos);
	//���߿� TransparentCopy(), PlgCopy()�� �߰��ϰ� ���� �޾Ƽ� �� �� �ְ� �� ��.
	

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
		GameEngineDebug::MsgBoxError("������ �� ���� ����� �̹��� �Ǻ��Դϴ�.");
		break;
	}
}

void GameEngineRenderer::CreateAnimation(const std::string& _animationName, const std::string& _imageName, int _startIndex, int _finishIndex, float _delayPerFrame, bool isRepetitive_, RenderPivot _pivot)
{
}