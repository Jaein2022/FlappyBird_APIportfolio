#include "PreCompile.h"
#include "GameEngineCollisionBody.h"
#include "GameEngineActor.h"

std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
GameEngineCollisionBody::checkCollisionFunctions_[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)]
= { nullptr };

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

void GameEngineCollisionBody::Initialize()
{
	for (int i = 0; i < static_cast<int>(CollisionBodyType::MAX); i++)
	{
		for (int j = 0; j < static_cast<int>(CollisionBodyType::MAX); j++)
		{
			checkCollisionFunctions_[i][j] = nullptr;
		}
	}

	checkCollisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::Line)]
		= std::bind(&GameEngineCollisionBody::RectToLine, std::placeholders::_1, std::placeholders::_2);

	checkCollisionFunctions_[static_cast<int>(CollisionBodyType::Rect)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::RectToRect, std::placeholders::_1, std::placeholders::_2);

	checkCollisionFunctions_[static_cast<int>(CollisionBodyType::Line)][static_cast<int>(CollisionBodyType::Line)]
		= std::bind(&GameEngineCollisionBody::LineToLine, std::placeholders::_1, std::placeholders::_2);

	checkCollisionFunctions_[static_cast<int>(CollisionBodyType::Line)][static_cast<int>(CollisionBodyType::Rect)]
		= std::bind(&GameEngineCollisionBody::LineToRect, std::placeholders::_1, std::placeholders::_2);

}

bool GameEngineCollisionBody::RectToLine(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right)
{
	return false;
}

bool GameEngineCollisionBody::RectToRect(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right)
{
	return false;
}

bool GameEngineCollisionBody::LineToLine(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right)
{
	GameEngineDebug::MsgBoxError("아직 구현하지 않은 종류의 충돌입니다.");
	return false;
}

bool GameEngineCollisionBody::LineToRect(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right)
{
	GameEngineDebug::MsgBoxError("아직 구현하지 않은 종류의 충돌입니다.");
	return false;
}

float4 GameEngineCollisionBody::GetWorldPos()
{
	return parentActor_->GetPos() + localPos_;
}