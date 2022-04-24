#include "PreCompile.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"

GameEngineImageManager* GameEngineImageManager::inst_ = new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager() : allImages_()
{
}

GameEngineImageManager::~GameEngineImageManager()
{
    for (const std::pair<std::string, GameEngineImage*>& imagePair : allImages_)
    {
        if (nullptr != imagePair.second)
        {
            delete imagePair.second;
        }
    }
    allImages_.clear();
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _path)
{
    return Load(GameEnginePath::GetFileName(_path), _path);
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _name, const std::string& _path)
{
    if (nullptr != Find(_name))
    {
        GameEngineDebug::MsgBoxError("파일이 이미 로드되어있습니다.");
        return nullptr;
    }

    GameEngineImage* newImage = new GameEngineImage();
    if (nullptr == newImage)
    {
        GameEngineDebug::MsgBoxError("파일 로드 실패.");
        delete newImage;
        return nullptr;
    }
    newImage->SetName(_name);

    //여기에 코드를 넣으세요.

    allImages_.insert(std::map<std::string, GameEngineImage*>::value_type(_name, newImage));
    return newImage;
}

GameEngineImage* GameEngineImageManager::Find(const std::string& _name)
{
    std::map<std::string, GameEngineImage*>::iterator findIter = allImages_.find(_name);
    if (allImages_.end() == findIter)
    {
        return nullptr;
    }
    else
    {
        return findIter->second;
    }

}