#include "PreCompile.h"
#include "GameEngineSound.h"
#include "GameEngineSoundManager.h"
#include "GameEngineSoundPlayer.h"
#include "GameEngineDebug.h"
#include "GameEnginePath.h" 
#include "GameEngineNameBase.h"

GameEngineSoundManager* GameEngineSoundManager::inst_ = new GameEngineSoundManager();

GameEngineSoundManager::GameEngineSoundManager() : soundSystem_(nullptr)
{
}

GameEngineSoundManager::~GameEngineSoundManager()
{
    for (std::list<GameEngineSoundPlayer*>::iterator it = allSoundPlayers_.begin();
        it != allSoundPlayers_.end(); it++)
    {
        if (nullptr != *it)
        {
            delete* it;
            *it = nullptr;
        }
    }
    allSoundPlayers_.clear();

    for (const std::pair<std::string, GameEngineSound*>& res : allSound_)
    {
        if (nullptr != res.second)
        {
            delete res.second;
        }
    }
    allSound_.clear();

    soundSystem_->release();
    soundSystem_ = nullptr;
}

void GameEngineSoundManager::Initialize()
{
    // �����ڵ忡�� new�� �� ���ɼ��� �ſ� ����.
    FMOD::System_Create(&soundSystem_);
    if (nullptr == soundSystem_)
    {
        GameEngineDebug::MsgBoxError("���� �ý��� ���� ����.");
        return;
    }

    if (FMOD_OK != soundSystem_->init(32, FMOD_DEFAULT, nullptr))
    {
        GameEngineDebug::MsgBoxError("���� �ý��� �ʱ�ȭ ����.");
        return;
    }
}

void GameEngineSoundManager::Update()
{
    if (nullptr == soundSystem_)
    {
        GameEngineDebug::MsgBoxError("����ý����� �����ϴ�.");
        return;
    }
    soundSystem_->update();
}

void GameEngineSoundManager::Load(const std::string& _path)
{
    Load(GameEnginePath::GetFileName(_path), _path);
}

void GameEngineSoundManager::Load(const std::string& _name, const std::string& _path)
{
    if (nullptr != Find(_name))
    {
        GameEngineDebug::MsgBoxError("�̹� �ε�� ���� �����Դϴ�.");
        return;
    }

    GameEngineSound* newSound = new GameEngineSound();
    if (false == newSound->Load(_path))
    {
        delete newSound;
        GameEngineDebug::MsgBoxError("�������� �ε� ����.");
        return;
    }
    newSound->SetName(_name);
    allSound_.insert(
        std::map<std::string, GameEngineSound*>::value_type(_name, newSound));
}

GameEngineSound* GameEngineSoundManager::Find(const std::string& _name)
{
    std::map<std::string, GameEngineSound*>::iterator findIter = allSound_.find(_name);
    if (allSound_.end() == findIter)
    {
        return nullptr;
    }
    else
    {
        return findIter->second;
    }
}

GameEngineSoundPlayer* GameEngineSoundManager::CreateSoundPlayer(const std::string& _playerName)
{
    GameEngineSoundPlayer* newSoundPlayer = new GameEngineSoundPlayer();
    newSoundPlayer->SetName(_playerName);
    allSoundPlayers_.push_back(newSoundPlayer);
    return newSoundPlayer;
}
