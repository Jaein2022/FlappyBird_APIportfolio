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
        GameEngineDebug::MsgBoxError("hInstance가 없습니다.");
        return;
    }

    if (true == _windowClassName.empty())
    {
        GameEngineDebug::MsgBoxError("윈도우클래스 이름이 없습니다.");
        return;
    }

    instanceHandle_ = _hInstance;
    windowClassName_ = _windowClassName;

    setlocale(  //로케일(세계 각 국마다 다른 문자, 숫자, 날짜 등의 표기에 관련된 매개변수 모음)을 설정하는 함수. 
        LC_ALL, //로케일 적용 범위. LC_ALL: 이 프로그램의 모든 부분에 로케일 세팅 적용.
        NULL    //언어 설정. NULL: OS 언어 설정을 따라감.
    );

    //WNDCLASSEXW: 아래의 구조체타입 변수 선언용 typedef.
    //typedef struct tagWNDCLASSEXW {
    //    UINT        cbSize;
    //    /* Win 3.x */
    //    UINT        style;            윈도우의 형태.
    //    WNDPROC     lpfnWndProc;      윈도우 관련 메시지를 처리할 함수 이름.    
    //    int         cbClsExtra;       여유 공간. 거의 쓰지 않음.
    //    int         cbWndExtra;       여유 공간. 거의 쓰지 않음.
    //    HINSTANCE   hInstance;        윈도우 클래스를 사용하는 프로그램(인스턴스)의 핸들.  
    //    HICON       hIcon;            윈도우 아이콘
    //    HCURSOR     hCursor;          윈도우에서 쓸 커서 형태.
    //    HBRUSH      hbrBackground;    윈도우 배경을 칠할 특정 색의 브러시 오브젝트 지정. +1: 백색, +2:회색
    //    LPCWSTR     lpszMenuName;     프로그램이 쓸 메뉴 지정. 사용하지 않을거라면 NULL
    //    LPCWSTR     lpszClassName;    윈도우 클래스의 이름. MyRegisterClass()를 통해 OS에 등록된 클래스이름과 다르면 실행되지 않는다.
    //    /* Win 4.0 */
    //    HICON       hIconSm;          윈도우가 최소화되면 사용할 아이콘.
    //} WNDCLASSEXW, * PWNDCLASSEXW, NEAR* NPWNDCLASSEXW, FAR* LPWNDCLASSEXW;

    WNDCLASSEXA wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;   //가로 | 세로 화면크기 갱신 옵션
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
        //위에서 설정한 옵션의 윈도우를 그리겠다고 OS에게 등록하는 함수. 실패하면 0을 반환.
    {
        GameEngineDebug::MsgBoxError("윈도우클래스 등록 실패.");
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
        GameEngineDebug::MsgBoxError("인스턴스 핸들이 없습니다.");
        return;
    }

    if (true == _windowTitle.empty())
    {
        GameEngineDebug::MsgBoxError("윈도우 타이틀이 없습니더.");
        return;
    }

    windowTitle_ = _windowTitle;

    windowHandle_ = CreateWindowA(
        windowClassName_.c_str(),       //윈도우 클래스 이름.
        windowTitle_.c_str(),           //윈도우 제목.
        WS_OVERLAPPEDWINDOW,            //윈도우 형태: 기본 윈도우.
        _windowPos.IntX(),              //윈도우 위치의 x좌표. 
        _windowPos.IntY(),              //윈도우 위치의 y좌표.
        _windowSize.IntX(),             //윈도우 가로길이.
        _windowSize.IntY(),             //윈도우 세로길이.
        nullptr,                        //부모 윈도우가 있다면 여기 넣는다.
        nullptr,                        //메뉴 핸들이 따로 있다면 여기 넣는다.
        instanceHandle_,                //윈도우를 만든 주체인 인스턴스의 핸들을 넣는다.
        nullptr                         //???
    );


    if (NULL == windowHandle_)
    {
        GameEngineDebug::MsgBoxError("윈도우핸들 생성 실패.");
        return;
    }

    ShowWindow(windowHandle_, SW_SHOW);
    UpdateWindow(windowHandle_);

    HDC windowHDC = ::GetDC(windowHandle_);
    if (nullptr == windowHDC)
    {
        GameEngineDebug::MsgBoxError("HDC 생성 실패.");
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
        GameEngineDebug::MsgBoxError("윈도우 크기 조정 실패.");
        return;
    }
}

void GameEngineWindow::Update(void(*UpdateFunctions)())
{
    //MSG: 아래 tagMSG 구조체타입 변수 생성용 typedef. 사용자가 입력한 정보를 저장한다.
    //    typedef struct tagMSG {
    //        HWND        hwnd;         //윈도우를 그릴 때 필요한 정보를 가지고 있는 핸들.
    //        UINT        message;      //사용자가 입력한 내용.
    //        WPARAM      wParam;       //세부적인 입력 내용.
    //        LPARAM      lParam;       //세부적인 입력 내용. WPARAM과 무슨 차이인지는 모르겠다.
    //        DWORD       time;         //입력 시간.
    //        POINT       pt;           //입력이 들어왔을때 마우스 포인터가 있던 위치.
    //#ifdef _MAC
    //        DWORD       lPrivate;     
    //#endif
    //    } MSG, * PMSG, NEAR* NPMSG, FAR* LPMSG;

    MSG msg = { 0 };

    while (isWindowOn)
    {
        if (nullptr == UpdateFunctions) //업데이트 함수포인터가 연결이 안되어있다면 폭파.
        {
            GameEngineDebug::MsgBoxError("업데이트 함수포인터가 없습니다.");
            return;
        }
        else
        {
            GameEngineTime::GetInst().Update();
            UpdateFunctions();
            //함수포인터도 변수처럼 쓰는 '함수'이므로 반드시 ()로 끝내줘야 한다.
            //GameEngineInput::GetInst().Update();
            //GameEngineSoundManager::GetInst().Update();
        }

        //GetMessageW(): 입력이 들어왔을때 다른 입력내용들은 첫번째 매개변수인 msg를 통해서 전달하고,
        //종료 명령일때만 false를 반환해서 루프를 끝내고 윈도우를 닫는다.
        //입력이 들어오든 들어오지 않든 게임은 계속 실행되어야 하므로 여기서는 사용하지 않는다. 
        if (0 != PeekMessage(   //상시 입력체크를 하다가 입력이 들어오면 0이 아닌 다른 값을 반환하고 msg에 입력의 자세한 내용을 저장하는 함수.
            &msg,               //들어온 입력의 구체적인 내용 전달.
            nullptr,            //윈도우 핸들. nullptr을 넣어주면 모든 윈도우의 메세지를 다 처리한다.
            0,                  //필터 최소??
            0,                  //필터 최대??
            PM_REMOVE           //지연되는 메시지 처리 방식 결정.
            //PM_REMOVE: 지연되는 메시지 지움. PM_NOREMOVE: 지연되는 메시지도 남김없이 처리함. PM_NOYIELD: ??
        ))      
           
        {
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
            {
                TranslateMessage(&msg); //TranslateMessage(): 사용자의 입력 내용을 정리, 변환해서 OS가 이해할 수 있는 형태로 만든다.
                DispatchMessage(&msg);  //DispatchMessage(): WndProc()함수로 메시지를 보낸다.
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
        //WM_PAINT 메시지가 들어왔을때 BeginPaint()함수가 없으면 다른 윈도우에 가려진 무효영역을 그리기 위해
        //루프 함수에 WM_PAINT 메시지가 무한정 들어와서 절대로 PeekMessage()함수가 0을 반환하지 않는다.
        //그래서 WM_PAINT메시지를 처리할 거라면 반드시 BeginPaint()함수를 사용해야 한다. 
        //아니면 아예 WM_PAINT 메시지 자체를 직접 받지 말고 DefWindowProc() 함수로 넘겨야 한다.
        //GetDC()함수는 WM_PAINT 메시지를 처리해주지 못하므로 의미 없다. 반드시 BeginPaint()여야 한다.
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
