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
#endif                      //���������� ���� ���� �ʴ´�.

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
