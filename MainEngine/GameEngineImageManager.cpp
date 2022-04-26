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

GameEngineImage* GameEngineImageManager::Load(const std::string& _path)
{
    return Load(GameEnginePath::GetFileName(_path), _path);
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _name, const std::string& _path)
{
    if (nullptr != Find(_name))
    {
        GameEngineDebug::MsgBoxError("이미지가 이미 로드되어있습니다.");
        return nullptr;
    }

    GameEngineImage* newImage = new GameEngineImage();
    if (false == newImage->Load(_path))
    {
        delete newImage;
        GameEngineDebug::MsgBoxError("이미지 로드 실패.");
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

void GameEngineImageManager::InitializeWindowImage(const HDC& _windowHDC)
{
    if (nullptr == _windowHDC)
    {
        GameEngineDebug::MsgBoxError("_windowHDC가 없습니다.");
        return;
    }

    backBufferImage_ = new GameEngineImage();
    backBufferImage_->Create(_windowHDC, GameEngineWindow::GetInst().GetWindowSize());

    frontBufferImage_ = new GameEngineImage();
    frontBufferImage_->Create(_windowHDC);
}

void GameEngineImageManager::CopyToFrontBuffer()
{
    frontBufferImage_->BitCopy(
        backBufferImage_,
        float4::ZERO,
        GameEngineWindow::GetInst().GetWindowSize(),
        float4::ZERO
    );
}
