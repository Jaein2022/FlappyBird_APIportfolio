#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"

GameEngineActor::GameEngineActor()
	: pos_(float4::ZERO),
	renderOrder_(-1),
	updateOrder_(-1)
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
	GameEngineRenderer* newRenderer = new GameEngineRenderer();
	newRenderer->SetName(_rendererName);
	newRenderer->SetParent(this);
	//newRenderer->SetActorImage(_imageName);
	
	std::pair<std::map<std::string, GameEngineRenderer*>::iterator, bool> insertResult = allRenderers_.insert(
		std::map<std::string, GameEngineRenderer*>::value_type(
			_rendererName, newRenderer));

	if (false == insertResult.second)
	{
		GameEngineDebug::MsgBoxError(insertResult.first->first + ": 이미 같은 이름의 렌더러가 존재합니다.");
		return;
	}
}
