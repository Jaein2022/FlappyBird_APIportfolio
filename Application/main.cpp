#include "PreCompile.h"

void InitializeGame();
void LoadResources();
void UpdateGame();
void DestroyGame();

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow
)
{
    GameEngineDebug::CheckLeak();

#ifdef _DEBUG               //디버그모드에서만 하고, 릴리즈모드에서는 하지 않는다.
    int* i = new int(1);	//릭 체크가 이루어지고 있는지를 확인하기 위한 의도적인 릭.
#endif                     

    GameEngineWindow::GetInst().RegisterWindowClass(hInstance, "FlappyBird_APIportfolio");
    GameEngineWindow::GetInst().CreateMainWindow("FlappyBird", { 400, 300 }, { 280, 500 + 30/*윈도우 타이틀바 폭*/});

    InitializeGame();

    LoadResources();


    GameEngineLevelManager::GetInst().Create<PlayLevel>("PlayLevel");
    GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel");



    GameEngineWindow::GetInst().Update(UpdateGame);


    DestroyGame();
}

void InitializeGame()
{
    GameEngineSoundManager::GetInst().Initialize();
    GameEngineCollisionBody::Initialize();
}

void LoadResources()
{
    GameEnginePath soundResourcePath = GameEnginePath();
    soundResourcePath.MoveToParent();
    soundResourcePath.MoveToChild("Resource");
    soundResourcePath.MoveToChild("Sound");
    std::vector<std::string> allSoundFileNames = soundResourcePath.CollectAllFileNames();
    for (size_t i = 0; i < allSoundFileNames.size(); i++)
    {
        GameEngineSoundManager::GetInst().Load(allSoundFileNames.at(i));
    }


    GameEnginePath imageResourcePath = GameEnginePath();
    imageResourcePath.MoveToParent();
    imageResourcePath.MoveToChild("Resource");
    imageResourcePath.MoveToChild("Image");
    std::vector<std::string> allImageFileNames = imageResourcePath.CollectAllFileNames();
    for (size_t i = 0; i < allImageFileNames.size(); i++)
    {
        GameEngineImageManager::GetInst().Load(allImageFileNames.at(i));
    }
}

void UpdateGame()
{
    GameEngineInput::GetInst().Update();
    GameEngineLevelManager::GetInst().Update();
    GameEngineSoundManager::GetInst().Update();
}

void DestroyGame()
{
    GameEngineLevelManager::Destroy();
    GameEngineRandom::Destroy();
    GameEngineImageManager::Destroy();
    GameEngineInput::Destroy();
    GameEngineWindow::Destroy();
    GameEngineSoundManager::Destroy();
    GameEngineTime::Destroy();
}
