#include "PreCompile.h"
#include "GameEngineSoundPlayer.h"
#include "GameEngineSound.h"
#include "GameEngineDebug.h"

GameEngineSoundPlayer::GameEngineSoundPlayer(): playChannel_(nullptr), playCount_(-1)
{
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}

bool GameEngineSoundPlayer::IsPlaying()
{
	bool check = false;
	playChannel_->isPlaying(&check);
	return check;
}

void GameEngineSoundPlayer::PlayCountReset(int _count)
{
	playCount_ = _count;
}

void GameEngineSoundPlayer::PlayOverLap(const std::string& _name, int _loopCount)
{
	GameEngineSound* soundPtr = GameEngineSoundManager::GetInst().Find(_name);

	if (nullptr == soundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (0 == playCount_)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		soundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--playCount_;

	playChannel_->setLoopCount(_loopCount);
}

void GameEngineSoundPlayer::PlayAlone(const std::string& _name, int _loopCount)
{
	GameEngineSound* soundPtr = GameEngineSoundManager::GetInst().Find(_name);

	if (nullptr == soundPtr)
	{
		GameEngineDebug::MsgBoxError(_name + ": 그런 이름의 사운드가 없습니다.");
		return;
	}

	if (true == IsPlaying())
	{
		return;
	}

	if (0 == playCount_)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		soundPtr->sound_
		, nullptr
		, false
		, &playChannel_
	);

	--playCount_;

	playChannel_->setLoopCount(_loopCount);
}

void GameEngineSoundPlayer::Stop()
{
	if (nullptr == playChannel_)
	{
		return;
	}
	playChannel_->stop();
	playChannel_ = nullptr;
}
