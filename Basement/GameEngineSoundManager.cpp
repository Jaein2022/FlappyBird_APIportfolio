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
    // 내부코드에서 NEW를 할 가능성이 매우 높다.
    FMOD::System_Create(&soundSystem_);
    if (nullptr == soundSystem_)
    {
        GameEngineDebug::MsgBoxError("사운드 시스템 생성 실패.");
        return;
    }

    if (FMOD_OK != soundSystem_->init(32, FMOD_DEFAULT, nullptr))
    {
        GameEngineDebug::MsgBoxError("사운드 시스템 초기화 실패.");
        return;
    }
}

void GameEngineSoundManager::Update()
{
    if (nullptr == soundSystem_)
    {
        GameEngineDebug::MsgBoxError("사운드시스템이 없습니다.");
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
        GameEngineDebug::MsgBoxError("이미 로드된 사운드 파일입니다.");
        return;
    }

    GameEngineSound* newSound = new GameEngineSound();
    if (false == newSound->Load(_path))
    {
        GameEngineDebug::MsgBoxError("사운드파일 로딩 실패.");
        delete newSound;
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

GameEngineSoundPlayer* GameEngineSoundManager::CreateSoundPlayer()
{
    GameEngineSoundPlayer* newSoundplayer = new GameEngineSoundPlayer();
    allSoundPlayers_.push_back(newSoundplayer);
    return  newSoundplayer;
}
