#pragma once
#include "LogicEnum.h"
#include "Bird.h"
#include "Pipe.h"

class Background;
class Pipe;
class Base;
class UI;
class PlayLevel : public GameEngineLevel
{
	//플레이레벨.


	friend class GameEngineLevelManager;
	friend void Pipe::ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	);	
	friend void Bird::ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	);

	//Member Variables.
	GameState currentState_;
	int score_;

	Bird* bird_;
	const float4 birdStartPos_;
	UI* UI_;

	std::vector<Background*> allBackgrounds_;
	const float4 backgroundSize_;
	const int backgroundCount_;

	std::vector<Base*> allBases_;
	const float4 baseSize_;
	const int basePosY_;
	const int baseCount_;

	std::vector<Pipe*> allPipes_;
	const int pipeStartPosX_;
	const int pipeInterval_;	//파이프 액터의 좌우 간격.
	const int pipeCount_;

	bool isDebuging_;
	const float playSpeed_;
	const float gravity_;


private:
	PlayLevel();
	~PlayLevel();

protected:
	PlayLevel(const PlayLevel& _other) = delete;
	PlayLevel(PlayLevel&& _other) noexcept = delete;

private:
	PlayLevel& operator=(const PlayLevel& _other) = delete;
	PlayLevel& operator=(const PlayLevel&& _other) = delete;


public:	


public:	
	GameState GetState() const
	{
		return currentState_;
	}
	int GetScore() const 
	{
		return score_;
	}
	bool IsDebuging() const
	{
		return isDebuging_;
	}
	const float GetGravity() const
	{
		return gravity_;
	}
	const float GetPlaySpeed() const
	{
		return playSpeed_;
	}


private:
	void Load() override;
	void UpdateLevel() override;
	void Reset();

private:
	void SetState(GameState _state)
	{
		currentState_ = _state;
	}
	void AddScore()
	{
		++score_;
	}
};

