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
		GameEngineDebug::MsgBoxError(_imageName + ": 그런 이름의 이미지가 없습니다.");
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
		GameEngineDebug::MsgBoxError(_ImageName + ": 그런 이름의 이미지가 없습니다.");
		return;
	}
}

void GameEngineRenderer::Render()
{
	GameEngineImage* backBufferImage = GameEngineImageManager::GetInst().GetBackBufferImage();

	if (nullptr == backBufferImage)
	{
		GameEngineDebug::MsgBoxError("백버퍼 이미지가 없습니다.");
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
		GameEngineDebug::MsgBoxError("지정할 수 없는 방식의 이미지 피봇입니다.");
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
		GameEngineDebug::MsgBoxError(_animationName + ": 이미 존재하는 애니메이션입니다.");
		return;
	}

	GameEngineImage* newAnimationImage = GameEngineImageManager::GetInst().Find(_imageName);
	if (nullptr == newAnimationImage)
	{
		GameEngineDebug::MsgBoxError(_imageName + ": 그런 이름의 이미지가 존재하지 않습니다.");
		return;
	}
	if (false == newAnimationImage->IsCut())	
	{
		GameEngineDebug::MsgBoxError("아직 잘리지 않은 이미지입니다.");
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
	if (nullptr != curAnimation_ &&					//기존 애니메이션도 진행하고 있고,
		false == _isForcedChange &&					//강제교체도 아니고,
		curAnimation_->GetName() == _animationName	//두 애니메이션 이름이 같으면 무시한다.
	)
	{
		return;
	}

	curAnimation_ = FindAnimation(_animationName);

	if (nullptr == curAnimation_)
	{
		GameEngineDebug::MsgBoxError(_animationName + ": 그런 이름의 애니메이션이 존재하지 않습니다.");
		return;
	}

	curAnimation_->Reset();
}

void GameEngineRenderer::UpdateAnimation()
{
	if (nullptr == curAnimation_)
	{
		GameEngineDebug::MsgBoxError("현재 진행중인 애니메이션이 없습니다.");
		return;
	}

	curAnimation_->Update();
}

void GameEngineRenderer::SetFrameIndex(int _index, RenderPivot _pivot)
{
	if (false == renderingImage_->IsCut())	
	{
		GameEngineDebug::MsgBoxError("아직 잘리지 않은 이미지입니다.");
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
		GameEngineDebug::MsgBoxError("사용할 수 없는 형태의 렌더피봇입니다.");
		return;
	}
}

bool GameEngineRenderer::IsCurAnimationFinished()
{
	if (nullptr == curAnimation_)
	{
		GameEngineDebug::MsgBoxError("현재 진행중인 애니메이션이 없습니다.");
		return false;
	}

	return curAnimation_->isFinished_;
}
