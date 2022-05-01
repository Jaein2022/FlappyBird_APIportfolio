#include "PreCompile.h"
#include "GameEngineCollisionBody.h"
#include "GameEngineActor.h"

GameEngineCollisionBody::GameEngineCollisionBody(GameEngineActor* _actor)
	: parentActor_(_actor),
	localPos_(float4::ZERO),
	size_(float4::ZERO),
	type_(CollisionBodyType::MAX),
	groupIndex_(0)
{
}

GameEngineCollisionBody::~GameEngineCollisionBody()
{
}


