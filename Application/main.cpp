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
    int* i = new int(1);	//�� üũ�� �̷������ �ִ����� Ȯ���ϱ� ���� �ǵ����� ��.
    (*i)++;
#endif                      //���������� ���� ���� �ʴ´�.


    GameEngineWindow::GetInst().Update(UpdateFunctions);









    GameEngineWindow::Destroy();
    GameEngineSoundManager::Destroy();
    GameEngineTime::Destroy();

}

void UpdateFunctions()
{

}
