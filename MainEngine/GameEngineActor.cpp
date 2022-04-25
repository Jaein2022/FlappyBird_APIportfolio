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


}
