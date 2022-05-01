#include "PreCompile.h"

void UpdateFunctions();

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

    GameEngineSoundManager::GetInst().Initialize();
    GameEngineWindow::GetInst().CreateMainWindowClass(hInstance, "FlappyBird_APIportfolio");
    GameEngineWindow::GetInst().CreateMainWindow("FlappyBird", float4::ZERO, { 800, 512 });

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

    GameEngineLevelManager::GetInst().Create<PlayLevel>("PlayLevel");
    GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel");






    GameEngineWindow::GetInst().Update(UpdateFunctions);



    GameEngineLevelManager::Destroy();
    GameEngineImageManager::Destroy();
    GameEngineInput::Destroy();
    GameEngineWindow::Destroy();
    GameEngineSoundManager::Destroy();
    GameEngineTime::Destroy();

}

void UpdateFunctions()
{


    GameEngineInput::GetInst().Update();
    GameEngineLevelManager::GetInst().Update();
    
    GameEngineSoundManager::GetInst().Update();
}
