#include "PreCompile.h"

void InitializeGame();
void LoadResource();
void UpdateGame();
void DestroyGame();

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow
)
{
    GameEngineDebug::LeakCheckOn();

#ifdef _DEBUG
    int* i = new int(1);	//�� üũ�� �̷������ �ִ����� Ȯ���ϱ� ���� �ǵ����� ��.
#endif                      //�������忡���� ���� �ʴ´�.

    GameEngineWindow::GetInst().RegisterWindowClass(hInstance, "FlappyBird_APIportfolio");
    GameEngineWindow::GetInst().CreateMainWindow("FlappyBird", { 400, 300 }, { 560, 512 + 30/*������ Ÿ��Ʋ�� ��*/});

    InitializeGame();

    LoadResource();


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

void LoadResource()
{
    GameEnginePath soundResourcePath = GameEnginePath();
    soundResourcePath.MoveToParent("FlappyBird_APIportfolio");
    soundResourcePath.MoveToChild("Resource");
    soundResourcePath.MoveToChild("Sound");
    std::vector<std::string> allSoundFileNames = soundResourcePath.CollectAllFileNames();
    for (size_t i = 0; i < allSoundFileNames.size(); i++)
    {
        GameEngineSoundManager::GetInst().Load(allSoundFileNames.at(i));
    }


    GameEnginePath imageResourcePath = GameEnginePath();
    imageResourcePath.MoveToParent("FlappyBird_APIportfolio");
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
