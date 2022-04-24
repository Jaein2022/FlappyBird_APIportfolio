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
        GameEngineDebug::MsgBoxError("������ �̹� �ε�Ǿ��ֽ��ϴ�.");
        return nullptr;
    }

    GameEngineImage* newImage = new GameEngineImage();
    if (nullptr == newImage)
    {
        GameEngineDebug::MsgBoxError("���� �ε� ����.");
        delete newImage;
        return nullptr;
    }
    newImage->SetName(_name);

    //���⿡ �ڵ带 ��������.

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