#include "PreCompile.h"
#include "GameEngineLevelManager.h"
#include "GameEngineImageManager.h"

GameEngineLevelManager* GameEngineLevelManager::inst_ = new GameEngineLevelManager();

GameEngineLevelManager::GameEngineLevelManager() 
    : curLevel_(nullptr),
    nextLevel_(nullptr)
{
}

GameEngineLevelManager::~GameEngineLevelManager()
{
    for (const std::pair<std::string, GameEngineLevel*>& levelPair : allLevels_)
    {
        if (nullptr != levelPair.second)
        {
            delete levelPair.second;
        }
    }
    allLevels_.clear();
}

void GameEngineLevelManager::ChangeLevel(const std::string& _levelName)
{
    nextLevel_ = Find(_levelName);
    
    if (nullptr == nextLevel_)
    {
        GameEngineDebug::MsgBoxError(_levelName + ": �������� �ʴ� �����Դϴ�.");
        return;
    }
}

void GameEngineLevelManager::Update()
{
    if (nullptr != nextLevel_)
    {
        curLevel_ = nextLevel_;
        nextLevel_ = nullptr;
        GameEngineTime::GetInst().Reset();
    }

    if (nullptr == curLevel_)
    {
        GameEngineDebug::MsgBoxError("���� ������ �����ϴ�.");
        return;
    }

    //������Ʈ ����, ������ ���� ����.
    curLevel_->SortUpdateOrder();
    curLevel_->SortRenderOrder();

    //���͵� ������Ʈ.
    curLevel_->Update();
    curLevel_->UpdateLevel();

    //���͵� ����(����ۿ� ������ �̹����� �߰�).
    curLevel_->Render();
    curLevel_->CheckCollision();
    GameEngineImageManager::GetInst().ExcuteDoubleBuffering();

    curLevel_->ReleaseDeadActor();
}

GameEngineLevel* GameEngineLevelManager::Find(const std::string& _name)
{
    std::map<std::string, GameEngineLevel*>::iterator findIter = allLevels_.find(_name);
    if (allLevels_.end() == findIter)
    {
        return nullptr;
    }
    else
    {
        return findIter->second;
    }
}