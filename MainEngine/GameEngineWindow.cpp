#include "PreCompile.h"
#include "GameEngineWindow.h"
#include "GameEngineInput.h"
#include "GameEngineImageManager.h"

GameEngineWindow* GameEngineWindow::inst_ = new GameEngineWindow();
bool isWindowOn = true;
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

GameEngineWindow::GameEngineWindow()
    : instanceHandle_(NULL),
    windowHandle_(NULL),
    windowClassName_(""),
    windowTitle_(""),
    windowSize_(float4::ZERO),
    windowPos_(float4::ZERO)
{
}

GameEngineWindow::~GameEngineWindow()
{
    if (nullptr != windowHandle_)
    {
        DestroyWindow(windowHandle_);
        windowHandle_ = nullptr;
    }
}

void GameEngineWindow::CreateMainWindowClass(HINSTANCE _hInstance, const std::string& _windowClassName)
{
    if (NULL == _hInstance)
    {
        GameEngineDebug::MsgBoxError("hInstance�� �����ϴ�.");
        return;
    }

    if (true == _windowClassName.empty())
    {
        GameEngineDebug::MsgBoxError("������Ŭ���� �̸��� �����ϴ�.");
        return;
    }

    instanceHandle_ = _hInstance;
    windowClassName_ = _windowClassName;

    setlocale(  //������(���� �� ������ �ٸ� ����, ����, ��¥ ���� ǥ�⿡ ���õ� �Ű����� ����)�� �����ϴ� �Լ�. 
        LC_ALL, //������ ���� ����. LC_ALL: �� ���α׷��� ��� �κп� ������ ���� ����.
        NULL    //��� ����. NULL: OS ��� ������ ����.
    );

    //WNDCLASSEXW: �Ʒ��� ����üŸ�� ���� ����� typedef.
    //typedef struct tagWNDCLASSEXW {
    //    UINT        cbSize;
    //    /* Win 3.x */
    //    UINT        style;            �������� ����.
    //    WNDPROC     lpfnWndProc;      ������ ���� �޽����� ó���� �Լ� �̸�.    
    //    int         cbClsExtra;       ���� ����. ���� ���� ����.
    //    int         cbWndExtra;       ���� ����. ���� ���� ����.
    //    HINSTANCE   hInstance;        ������ Ŭ������ ����ϴ� ���α׷�(�ν��Ͻ�)�� �ڵ�.  
    //    HICON       hIcon;            ������ ������
    //    HCURSOR     hCursor;          �����쿡�� �� Ŀ�� ����.
    //    HBRUSH      hbrBackground;    ������ ����� ĥ�� Ư�� ���� �귯�� ������Ʈ ����. +1: ���, +2:ȸ��
    //    LPCWSTR     lpszMenuName;     ���α׷��� �� �޴� ����. ������� �����Ŷ�� NULL
    //    LPCWSTR     lpszClassName;    ������ Ŭ������ �̸�. MyRegisterClass()�� ���� OS�� ��ϵ� Ŭ�����̸��� �ٸ��� ������� �ʴ´�.
    //    /* Win 4.0 */
    //    HICON       hIconSm;          �����찡 �ּ�ȭ�Ǹ� ����� ������.
    //} WNDCLASSEXW, * PWNDCLASSEXW, NEAR* NPWNDCLASSEXW, FAR* LPWNDCLASSEXW;

    WNDCLASSEXA wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;   //���� | ���� ȭ��ũ�� ���� �ɼ�
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instanceHandle_;

    wcex.hIcon = nullptr;
    wcex.hCursor = nullptr;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = windowClassName_.c_str();
    wcex.hIconSm = nullptr;

    if (0 == RegisterClassExA(&wcex))
        //������ ������ �ɼ��� �����츦 �׸��ڴٰ� OS���� ����ϴ� �Լ�. �����ϸ� 0�� ��ȯ.
    {
        GameEngineDebug::MsgBoxError("������Ŭ���� ��� ����.");
        return;
    }
}

void GameEngineWindow::CreateMainWindow(
    const std::string& _windowTitle,
    const float4& _windowPos,
    const float4& _windowSize
)
{
    if (NULL == instanceHandle_)
    {
        GameEngineDebug::MsgBoxError("�ν��Ͻ� �ڵ��� �����ϴ�.");
        return;
    }

    if (true == _windowTitle.empty())
    {
        GameEngineDebug::MsgBoxError("������ Ÿ��Ʋ�� �����ϴ�.");
        return;
    }

    windowTitle_ = _windowTitle;

    windowHandle_ = CreateWindowA(
        windowClassName_.c_str(),       //������ Ŭ���� �̸�.
        windowTitle_.c_str(),           //������ ����.
        WS_OVERLAPPEDWINDOW,            //������ ����: �⺻ ������.
        _windowPos.IntX(),              //������ ��ġ�� x��ǥ. 
        _windowPos.IntY(),              //������ ��ġ�� y��ǥ.
        _windowSize.IntX(),             //������ ���α���.
        _windowSize.IntY(),             //������ ���α���.
        nullptr,                        //�θ� �����찡 �ִٸ� ���� �ִ´�.
        nullptr,                        //�޴� �ڵ��� ���� �ִٸ� ���� �ִ´�.
        instanceHandle_,                //�����츦 ���� ��ü�� �ν��Ͻ��� �ڵ��� �ִ´�.
        nullptr                         //???
    );


    if (NULL == windowHandle_)
    {
        GameEngineDebug::MsgBoxError("�������ڵ� ���� ����.");
        return;
    }

    ShowWindow(windowHandle_, SW_SHOW);
    UpdateWindow(windowHandle_);

    HDC windowHDC = ::GetDC(windowHandle_);
    if (nullptr == windowHDC)
    {
        GameEngineDebug::MsgBoxError("HDC ���� ����.");
        return;
    }

    GameEngineImageManager::GetInst().InitializeWindowImage(windowHDC);

}

void GameEngineWindow::SetWindowPosAndSize(const float4& _windowPos, const float4& _windowSize)
{
    windowPos_ = _windowPos;
    windowSize_ = _windowSize;
    RECT windowRect = { 0, 0, windowSize_.IntX(), windowSize_.IntY() };

    AdjustWindowRect(           //
        &windowRect,            //
        WS_OVERLAPPEDWINDOW,    //
        false                   //
    );

    if (0 == SetWindowPos(                      //
        windowHandle_,                          //
        HWND_TOP,                               //
        windowPos_.IntX(),                      //
        windowPos_.IntY(),                      //
        windowRect.right - windowRect.left,     //
        windowRect.bottom - windowRect.top,     //
        0                                       //
    ))
    {
        GameEngineDebug::MsgBoxError("������ ũ�� ���� ����.");
        return;
    }
}

void GameEngineWindow::Update(void(*UpdateFunctions)())
{
    //MSG: �Ʒ� tagMSG ����üŸ�� ���� ������ typedef. ����ڰ� �Է��� ������ �����Ѵ�.
    //    typedef struct tagMSG {
    //        HWND        hwnd;         //�����츦 �׸� �� �ʿ��� ������ ������ �ִ� �ڵ�.
    //        UINT        message;      //����ڰ� �Է��� ����.
    //        WPARAM      wParam;       //�������� �Է� ����.
    //        LPARAM      lParam;       //�������� �Է� ����. WPARAM�� ���� ���������� �𸣰ڴ�.
    //        DWORD       time;         //�Է� �ð�.
    //        POINT       pt;           //�Է��� �������� ���콺 �����Ͱ� �ִ� ��ġ.
    //#ifdef _MAC
    //        DWORD       lPrivate;     
    //#endif
    //    } MSG, * PMSG, NEAR* NPMSG, FAR* LPMSG;

    MSG msg = { 0 };

    while (isWindowOn)
    {
        if (nullptr == UpdateFunctions) //������Ʈ �Լ������Ͱ� ������ �ȵǾ��ִٸ� ����.
        {
            GameEngineDebug::MsgBoxError("������Ʈ �Լ������Ͱ� �����ϴ�.");
            return;
        }
        else
        {
            GameEngineTime::GetInst().Update();
            UpdateFunctions();
            //�Լ������͵� ����ó�� ���� '�Լ�'�̹Ƿ� �ݵ�� ()�� ������� �Ѵ�.
            //GameEngineInput::GetInst().Update();
            //GameEngineSoundManager::GetInst().Update();
        }

        //GetMessageW(): �Է��� �������� �ٸ� �Է³������ ù��° �Ű������� msg�� ���ؼ� �����ϰ�,
        //���� ����϶��� false�� ��ȯ�ؼ� ������ ������ �����츦 �ݴ´�.
        //�Է��� ������ ������ �ʵ� ������ ��� ����Ǿ�� �ϹǷ� ���⼭�� ������� �ʴ´�. 
        if (0 != PeekMessage(   //��� �Է�üũ�� �ϴٰ� �Է��� ������ 0�� �ƴ� �ٸ� ���� ��ȯ�ϰ� msg�� �Է��� �ڼ��� ������ �����ϴ� �Լ�.
            &msg,               //���� �Է��� ��ü���� ���� ����.
            nullptr,            //������ �ڵ�. nullptr�� �־��ָ� ��� �������� �޼����� �� ó���Ѵ�.
            0,                  //���� �ּ�??
            0,                  //���� �ִ�??
            PM_REMOVE           //�����Ǵ� �޽��� ó�� ��� ����.
            //PM_REMOVE: �����Ǵ� �޽��� ����. PM_NOREMOVE: �����Ǵ� �޽����� ������� ó����. PM_NOYIELD: ??
        ))      
           
        {
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
            {
                TranslateMessage(&msg); //TranslateMessage(): ������� �Է� ������ ����, ��ȯ�ؼ� OS�� ������ �� �ִ� ���·� �����.
                DispatchMessage(&msg);  //DispatchMessage(): WndProc()�Լ��� �޽����� ������.
            }
        }
    }
}

void GameEngineWindow::TurnOffWindow()
{
    isWindowOn = false;
}

LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_PAINT:
    {
        //WM_PAINT �޽����� �������� BeginPaint()�Լ��� ������ �ٸ� �����쿡 ������ ��ȿ������ �׸��� ����
        //���� �Լ��� WM_PAINT �޽����� ������ ���ͼ� ����� PeekMessage()�Լ��� 0�� ��ȯ���� �ʴ´�.
        //�׷��� WM_PAINT�޽����� ó���� �Ŷ�� �ݵ�� BeginPaint()�Լ��� ����ؾ� �Ѵ�. 
        //�ƴϸ� �ƿ� WM_PAINT �޽��� ��ü�� ���� ���� ���� DefWindowProc() �Լ��� �Ѱܾ� �Ѵ�.
        //GetDC()�Լ��� WM_PAINT �޽����� ó�������� ���ϹǷ� �ǹ� ����. �ݵ�� BeginPaint()���� �Ѵ�.
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        isWindowOn = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }
    return 0;
}
