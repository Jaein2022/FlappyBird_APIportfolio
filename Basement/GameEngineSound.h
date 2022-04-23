#pragma once
#include "GameEngineSoundManager.h"
#include "GameEngineNameBase.h"


class GameEngineSound: public GameEngineNameBase
{

	//Friend Classes
	friend class GameEngineSoundManager;
	friend class GameEngineSoundPlayer;

	//Member Variables
	FMOD::Sound* sound_;



public:
	GameEngineSound();
	~GameEngineSound();

protected:
	GameEngineSound(const GameEngineSound& _other) = delete;
	GameEngineSound(GameEngineSound&& _other) noexcept = delete;

private:
	GameEngineSound& operator=(const GameEngineSound& _other) = delete;
	GameEngineSound& operator=(const GameEngineSound&& _other) = delete;


public:	//Member Function Headers
	bool Load(const std::string& _path);


};

