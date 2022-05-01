#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineActor.h"

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
	parentRenderer_->SetFrameIndex(curIndex_, pivot_);
}




GameEngineRenderer::GameEngineRenderer(GameEngineActor* _actor)
	: parentActor_(_actor),
	renderingImage_(nullptr),
	renderingImagePos_(float4::ZERO),
	renderingImageSize_(float4::ZERO),
	renderingImagePivot_(float4::ZERO),
	angle_(0.000f),
	renderSize_(float4::ZERO),
	rendererLocalPos_(float4::ZERO),
	maskImage_(nullptr),
	curAnimation_(nullptr),
	isCameraEffect_(false)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
	for (std::pair<std::string, Animation*> animationPair : allAnimations_)
	{
		if (nullptr != animationPair.second)
		{
			delete animationPair.second;
			animationPair.second = nullptr;
		}
	}
	allAnimations_.clear();
}

void GameEngineRenderer::SetImage(const std::string& _imageName)
{
	renderingImage_ = GameEngineImageManager::GetInst().Find(_imageName);
	if (nullptr == renderingImage_)
	{
		GameEngineDebug::MsgBoxError(_imageName + ": �׷� �̸��� �̹����� �����ϴ�.");
		return;
	}

	renderSize_ = renderingImage_->GetSize();
	renderingImageSize_ = renderingImage_->GetSize();
}

void GameEngineRenderer::SetMaskImage(const std::string& _ImageName)
{
	maskImage_ = GameEngineImageManager::GetInst().Find(_ImageName);
	if (nullptr == maskImage_)
	{
		GameEngineDebug::MsgBoxError(_ImageName + ": �׷� �̸��� �̹����� �����ϴ�.");
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
	
	float4 renderPos = float4::ZERO;
	if (true == isCameraEffect_)
	{
		renderPos = parentActor_->GetCameraPos() + rendererLocalPos_ - renderingImagePivot_;
	}
	else
	{
		renderPos = parentActor_->GetPos() + rendererLocalPos_ - renderingImagePivot_;
	}
	
	if (0.000f == angle_)
	{
		backBufferImage->TransparentCopy(
			renderingImage_,
			renderPos,
			renderSize_,
			renderingImagePos_,
			renderingImageSize_,
			RGB(255, 0, 255)
		);
	}
	else
	{
		backBufferImage->PlgCopy(
			renderingImage_,
			renderPos,
			renderingImageSize_,
			maskImage_,
			angle_
		);
	}
}

void GameEngineRenderer::SetRenderingImagePivot(RenderPivot _pivot)
{
	switch (_pivot)
	{
	case RenderPivot::Center:
		renderingImagePivot_ = renderingImage_->GetSize().Half();
		break;
	case RenderPivot::Bottom:
		renderingImagePivot_ = renderingImage_->GetSize().Half();
		renderingImagePivot_.y = renderingImage_->GetSize().y;
		break;
	case RenderPivot::LeftTop:
		renderingImagePivot_ = float4::ZERO;
		break;

	default:
		GameEngineDebug::MsgBoxError("������ �� ���� ����� �̹��� �Ǻ��Դϴ�.");
		break;
	}
}

void GameEngineRenderer::CreateAnimation(
	const std::string& _animationName,
	const std::string& _imageName,
	int _startIndex,
	int _finishIndex,
	float _delayPerFrame,
	bool _isRepetitive /*= true*/,
	RenderPivot _pivot /*= RenderPivot::CENTER*/
)
{
	if (nullptr != FindAnimation(_animationName))
	{
		GameEngineDebug::MsgBoxError(_animationName + ": �̹� �����ϴ� �ִϸ��̼��Դϴ�.");
		return;
	}

	GameEngineImage* newAnimationImage = GameEngineImageManager::GetInst().Find(_imageName);
	if (nullptr == newAnimationImage)
	{
		GameEngineDebug::MsgBoxError(_imageName + ": �׷� �̸��� �̹����� �������� �ʽ��ϴ�.");
		return;
	}
	if (false == newAnimationImage->IsCut())	
	{
		GameEngineDebug::MsgBoxError("���� �߸��� ���� �̹����Դϴ�.");
		return;
	}
	
	renderingImage_ = newAnimationImage;

	Animation* newAnimation = new Animation(this);

	newAnimation->startIndex_ = _startIndex;
	newAnimation->curIndex_ = _startIndex;
	newAnimation->finishIndex_ = _finishIndex;
	newAnimation->delayPerFrame_ = _delayPerFrame;
	newAnimation->pivot_ = _pivot;
	newAnimation->SetParent(this);
	newAnimation->isRepetitive_ = _isRepetitive;
	newAnimation->SetName(_animationName);

	allAnimations_.insert(
		std::map<std::string, Animation*>::value_type(
			_animationName, newAnimation));
}

GameEngineRenderer::Animation* GameEngineRenderer::FindAnimation(const std::string& _animationName)
{
	std::map<std::string, Animation*>::iterator findIter = allAnimations_.find(_animationName);
	if (allAnimations_.end() == findIter)
	{
		return nullptr;
	}
	else
	{
		return findIter->second;
	}
}

void GameEngineRenderer::ChangeAnimation(const std::string& _animationName, bool _isForcedChange /*= false*/)
{
	if (nullptr != curAnimation_ &&					//���� �ִϸ��̼ǵ� �����ϰ� �ְ�,
		false == _isForcedChange &&					//������ü�� �ƴϰ�,
		curAnimation_->GetName() == _animationName	//�� �ִϸ��̼� �̸��� ������ �����Ѵ�.
	)
	{
		return;
	}

	curAnimation_ = FindAnimation(_animationName);

	if (nullptr == curAnimation_)
	{
		GameEngineDebug::MsgBoxError(_animationName + ": �׷� �̸��� �ִϸ��̼��� �������� �ʽ��ϴ�.");
		return;
	}

	curAnimation_->Reset();
}

void GameEngineRenderer::UpdateAnimation()
{
	if (nullptr == curAnimation_)
	{
		GameEngineDebug::MsgBoxError("���� �������� �ִϸ��̼��� �����ϴ�.");
		return;
	}

	curAnimation_->Update();
}

void GameEngineRenderer::SetFrameIndex(int _index, RenderPivot _pivot)
{
	if (false == renderingImage_->IsCut())	
	{
		GameEngineDebug::MsgBoxError("���� �߸��� ���� �̹����Դϴ�.");
		return;
	}

	renderingImagePos_ = renderingImage_->GetCuttingPos(_index);
	renderingImageSize_ = renderingImage_->GetCuttingSizes(_index);
	renderSize_ = renderingImageSize_;

	switch (_pivot)
	{
	case RenderPivot::Center:
		renderingImagePivot_ = renderSize_.Half();
		break;
	case RenderPivot::Bottom:
		renderingImagePivot_ = renderSize_.Half();
		renderingImagePivot_.y += renderSize_.Half().y;
		break;
	case RenderPivot::LeftTop:
		renderingImagePivot_ = float4::ZERO;
		break;

	default:
		GameEngineDebug::MsgBoxError("����� �� ���� ������ �����Ǻ��Դϴ�.");
		return;
	}
}

bool GameEngineRenderer::IsCurAnimationFinished()
{
	if (nullptr == curAnimation_)
	{
		GameEngineDebug::MsgBoxError("���� �������� �ִϸ��̼��� �����ϴ�.");
		return false;
	}

	return curAnimation_->isFinished_;
}
