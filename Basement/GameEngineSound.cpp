#include "PreCompile.h"
#include "GameEngineSound.h"
#include "GameEngineDebug.h"

GameEngineSound::GameEngineSound(): sound_(nullptr)
{
}

GameEngineSound::~GameEngineSound()
{
}

bool GameEngineSound::Load(const std::string& _path)
{
	if (FMOD_RESULT::FMOD_OK !=
		GameEngineSoundManager::GetInst().soundSystem_->createSound(
			_path.c_str(),
			FMOD_LOOP_NORMAL,
			nullptr,
			&sound_
	))
	{
		GameEngineDebug::MsgBoxError("사운드파일을 불러오는데 실패했습니다.");
		return false;
	}

	if (nullptr == sound_)
	{
		GameEngineDebug::MsgBoxError("사운드가 널포인터입니다.");
		return false;
	}

	return true;
}
