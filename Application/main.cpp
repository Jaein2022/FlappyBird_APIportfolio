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

    GameEngineSoundManager::GetInst().Initialize();
    GameEngineWindow::GetInst().CreateMainWindowClass(hInstance, "API_Portfolio");
    GameEngineWindow::GetInst().CreateMainWindow("FlappyBird", float4::ZERO, { 1280, 720 });

#ifdef _DEBUG
    int* i = new int(1);	//릭 체크가 이루어지고 있는지를 확인하기 위한 의도적인 릭.
    (*i)++;
#endif                      //릴리즈모드일 때는 하지 않는다.


    GameEngineWindow::GetInst().Update(UpdateFunctions);









    GameEngineWindow::Destroy();
    GameEngineSoundManager::Destroy();
    GameEngineTime::Destroy();

}

void UpdateFunctions()
{

}
