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
    int* i = new int(1);	//릭 체크가 이루어지고 있는지를 확인하기 위한 의도적인 릭.
#endif                      //릴리즈모드일 때는 하지 않는다.

    GameEngineSoundManager::GetInst().Initialize();
    GameEngineWindow::GetInst().CreateMainWindowClass(hInstance, "FlappyBird_APIportfolio");
    GameEngineWindow::GetInst().CreateMainWindow("FlappyBird", float4::ZERO, { 1280, 720 });

    GameEnginePath* tempPath = new GameEnginePath();
    tempPath->MoveToParent("FlappyBird_APIportfolio");
    tempPath->MoveToChild("Resource");
    tempPath->MoveToChild("Sound");
    
    std::vector<const std::string&> allSoundFileNames = tempPath->CollectAllFileNames();

    for (size_t i = 0; i < allSoundFileNames.size(); i++)
    {
        GameEngineSoundManager::GetInst().Load(allSoundFileNames.at(i));
    }

          

    GameEngineInput::GetInst().CreateKey("Space", ' ');


    GameEngineWindow::GetInst().Update(UpdateFunctions);







    GameEngineImageManager::Destroy();
    GameEngineInput::Destroy();
    GameEngineWindow::Destroy();
    GameEngineSoundManager::Destroy();
    GameEngineTime::Destroy();

}

void UpdateFunctions()
{


    GameEngineInput::GetInst().Update();

    
    GameEngineSoundManager::GetInst().Update();
}
