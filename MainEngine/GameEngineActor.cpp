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

float4 GameEngineActor::GetCameraPos()
{
	return this->pos_ - parentLevel_->GetCameraPos();
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _imageName, const std::string& _rendererName)
{
	GameEngineRenderer* newRenderer = new GameEngineRenderer(this);
	newRenderer->SetParent(this);
	newRenderer->SetImage(_imageName);
	newRenderer->SetName(_rendererName);
	
	allRenderers_.push_back(newRenderer);

	return newRenderer;
}

GameEngineCollisionBody* GameEngineActor::CreateCollisionBody(
	const std::string& _collisionBodyName,
	const float4& _color,
	CollisionBodyType _type
)
{
	GameEngineCollisionBody* newCollisionBody = new GameEngineCollisionBody(this);
	newCollisionBody->SetParent(this);
	newCollisionBody->SetType(_type);
	newCollisionBody->SetName(_collisionBodyName);
	newCollisionBody->SetColor(_color);
	allCollisionBodies_.push_back(newCollisionBody);

	return newCollisionBody;
}

void GameEngineActor::CheckCollision(GameEngineActor* _other)
{
	for (GameEngineCollisionBody* const otherCollisionBody : _other->GetCollisionBodies())
	{
		for (GameEngineCollisionBody* const thisCollisionBody : this->GetCollisionBodies())
		{
			bool collisionResult =
				GameEngineCollisionBody::collisionFunctions_
				[thisCollisionBody->GetTypeInt()][otherCollisionBody->GetTypeInt()]
				(thisCollisionBody, otherCollisionBody);

			if (true == collisionResult)
			{
				ReactCollision();
			}
		}
	}
}


