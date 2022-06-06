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
	void PlayOverLap(const std::string& _name, int _loopCount = 1);	// ���ļ� ��� ������ ���尡 ����ǰ� �־ �׳� ����Ѵ�.
	void PlayAlone(const std::string& _name, int _loopCount = 1);	// ������ ���尡 ����� �����߸� ���� ���带 ����Ѵ�.
	void Stop();


};

