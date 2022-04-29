#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
	: parentLevel_(nullptr),
	pos_(float4::ZERO),
	renderOrder_(0),
	updateOrder_(0)
{
}

GameEngineActor::~GameEngineActor()
{
	for (std::pair<std::string, GameEngineRenderer*> rendererPair: allRenderers_)
	{
		if (nullptr != rendererPair.second)
		{
			delete rendererPair.second;
			rendererPair.second = nullptr;
		}
	}
}

void GameEngineActor::CreateRenderer(const std::string& _imageName, const std::string& _rendererName)
{
	GameEngineRenderer* newRenderer = new GameEngineRenderer(this);
	newRenderer->SetName(_rendererName);
	newRenderer->SetParent(this);
	newRenderer->SetImage(_imageName);
	
	std::pair<std::map<std::string, GameEngineRenderer*>::iterator, bool> insertResult = allRenderers_.insert(
		std::map<std::string, GameEngineRenderer*>::value_type(
			_rendererName, newRenderer));

	if (false == insertResult.second)
	{
		GameEngineDebug::MsgBoxError(insertResult.first->first + ": 같은 이름의 렌더러가 이미 존재합니다.");
		return;
	}
}

float4 GameEngineActor::GetCamPos()
{
	return this->pos_ - parentLevel_->GetCameraPos();
}
