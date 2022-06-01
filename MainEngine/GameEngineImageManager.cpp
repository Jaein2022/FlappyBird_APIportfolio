#include "PreCompile.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineWindow.h"

GameEngineImageManager* GameEngineImageManager::inst_ = new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager() 
    : allImages_(), frontBufferImage_(nullptr), backBufferImage_(nullptr)
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

    if (nullptr != frontBufferImage_)
    {
        delete frontBufferImage_;
        frontBufferImage_ = nullptr;
    }

    if (nullptr != backBufferImage_)
    {
        delete backBufferImage_;
        backBufferImage_ = nullptr;
    }
}

void GameEngineImageManager::Load(const std::string& _path)
{
    Load(GameEnginePath::GetFileName(_path), _path);
}

void GameEngineImageManager::Load(const std::string& _name, const std::string& _path)
{
    if (nullptr != Find(_name))
    {
        GameEngineDebug::MsgBoxError("�̹����� �̹� �ε�Ǿ��ֽ��ϴ�.");
        return;
    }

    GameEngineImage* newImage = new GameEngineImage();
    if (false == newImage->Load(_path))
    {
        delete newImage;
        GameEngineDebug::MsgBoxError("�̹��� �ε� ����.");
        return;
    }
    newImage->SetName(_name);
    allImages_.insert(std::map<std::string, GameEngineImage*>::value_type(_name, newImage));
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

void GameEngineImageManager::InitializeWindowImage(const HDC& _windowHDC)
{
    if (nullptr == _windowHDC)
    {
        GameEngineDebug::MsgBoxError("_windowHDC�� �����ϴ�.");
        return;
    }

    backBufferImage_ = new GameEngineImage();
    backBufferImage_->Create(_windowHDC, GameEngineWindow::GetInst().GetWindowSize());

    frontBufferImage_ = new GameEngineImage();
    frontBufferImage_->Create(_windowHDC);
}

void GameEngineImageManager::ExcuteDoubleBuffering()
{
    frontBufferImage_->BitCopy(
        backBufferImage_,
        float4::Zero,
        GameEngineWindow::GetInst().GetWindowSize(),
        float4::Zero
    );
}
