#include "PreCompile.h"
#include "GameEngineObjectBase.h"

GameEngineObjectBase::GameEngineObjectBase()
	: isDead_(false), isUpdateOn_(true), isDebugChecked_(false), parentObject_(nullptr)
{
}

GameEngineObjectBase::~GameEngineObjectBase()
{
}