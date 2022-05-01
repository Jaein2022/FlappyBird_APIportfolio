#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCollisionBody.h"

GameEngineActor::GameEngineActor()
	: parentLevel_(nullptr),
	pos_(float4::ZERO),
	renderOrder_(0),
	updateOrder_(0)
{
}

GameEngineActor::~GameEngineActor()
{
	for (GameEngineRenderer* renderer : allRenderers_)
	{
		if (nullptr != renderer)
		{
			delete renderer;
			renderer = nullptr;
		}
	}

	for (GameEngineCollisionBody* collisionBody : allCollisionBodies_)
	{
		if (nullptr != collisionBody)
		{
			delete collisionBody;
			collisionBody = nullptr;
		}
	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _imageName, const std::string& _rendererName)
{
	GameEngineRenderer* newRenderer = new GameEngineRenderer(this);
	//newRenderer->parentActor_ = this;
	newRenderer->SetParent(this);
	newRenderer->SetImage(_imageName);
	newRenderer->SetName(_rendererName);
	
	allRenderers_.push_back(newRenderer);

	return newRenderer;
}

GameEngineCollisionBody* GameEngineActor::CreateCollisionBody(
	const std::string& _collisionBodyName,
	int _collisionGroupIndex,
	CollisionBodyType _type
)
{
	GameEngineCollisionBody* newCollisionBody = new GameEngineCollisionBody(this);
	newCollisionBody->SetParent(this);
	newCollisionBody->SetType(_type);
	newCollisionBody->SetGroup(_collisionGroupIndex);
	newCollisionBody->SetName(_collisionBodyName);
	allCollisionBodies_.push_back(newCollisionBody);

	parentLevel_->InsertCollsionBody(_collisionGroupIndex, newCollisionBody);	
	//콜리전그룹 필요 없어지면 삭제.

	return newCollisionBody;
}

float4 GameEngineActor::GetCameraPos()
{
	return this->pos_ - parentLevel_->GetCameraPos();
}
