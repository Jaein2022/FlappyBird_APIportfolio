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
		GameEngineDebug::MsgBoxError("���������� �ҷ����µ� �����߽��ϴ�.");
		return false;
	}

	if (nullptr == sound_)
	{
		GameEngineDebug::MsgBoxError("���尡 ���������Դϴ�.");
		return false;
	}

	return true;
}
