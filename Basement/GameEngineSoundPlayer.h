#pragma once
#include "GameEngineSoundManager.h"
#include "GameEngineNameBase.h"

class GameEngineSoundPlayer: public GameEngineNameBase
{
	//Friend Classes
	friend GameEngineSoundManager;

	//Member Variables
	FMOD::Channel* playChannel_;
	int playCount_;


public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();

protected:
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _other) = delete;
	GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept = delete;

private:
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer& _other) = delete;
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer&& _other) = delete;


public:	//Member Function Headers
	bool IsPlaying();
	void ResetPlayCount(int _count = -1);
	void PlayOverLap(const std::string& _name, int _loopCount = 1);	// 겹쳐서 재생 기존의 사운드가 재생되고 있어도 그냥 재생한다.
	void PlayAlone(const std::string& _name, int _loopCount = 1);	// 기존의 사운드가 재생이 끝나야만 다음 사운드를 재생한다.
	void Stop();


};

