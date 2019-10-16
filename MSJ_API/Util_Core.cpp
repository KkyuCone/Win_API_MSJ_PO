#include "stdafx.h"
#include <locale>

// 그 외 나머지 프로젝트 헤더
#include "Resource.h"
#include "Util_Core.h"
#include "TAssert.h"
#include "Render_Vector.h"

#include "MainSceneState.h"
#include "ResourceManager.h"
 

bool Util_Core::m_UtilCore_Life = true;

Util_Core::Util_Core()
	: m_hInstance(nullptr), m_Hwnd(nullptr)
	, m_pCurStage(nullptr), m_AllStage(ALLSTAGE::MAX), m_pNextStage(nullptr)
	, m_SceneSize(1024, 768)
{
}


Util_Core::~Util_Core()
{
	for (size_t i = 0; i < m_AllStage.size(); i++)
	{
		if (nullptr != m_AllStage[i])
		{
			delete m_AllStage[i];
			m_AllStage[i] = nullptr;
		}
	}
}

//////////////////////////////////////////////////////////////////

int Util_Core::WinAPI_Start(HINSTANCE _hInstance)
{
	Tassert(nullptr == _hInstance);

	if (nullptr == _hInstance)
	{
		return -1;
	}

	m_hInstance = _hInstance;

	_wsetlocale(LC_ALL, L"KOR");
	MyRegisterClass(m_hInstance);

	if (!InitInstance(m_hInstance))
	{
		return FALSE;
	}

	MSG msg;

	ResourceManager::Instance().ResMgr_Init();

	UserInit();

	while (true == m_UtilCore_Life)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Progress();
		}
	}

	return (int)msg.wParam;
}

// 윈도우 프로시저 - 윈도우 메시지 처리 함수 
LRESULT CALLBACK Util_Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		m_UtilCore_Life = false;
		//PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);;
}

// 윈도우 형태 + 클래스 정의와 등록 
ATOM Util_Core::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY_WIN32API));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	ShowCursor(FALSE);

	return RegisterClassExW(&wcex);
}


BOOL Util_Core::InitInstance(HINSTANCE hInstance)
{
	m_Hwnd = CreateWindowW(L"WindowClass", L"Window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	if (!m_Hwnd)
	{
		return FALSE;
	}

	RECT Rect = { 0, 0, m_SceneSize.X, m_SceneSize.Y };

	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_Hwnd, nullptr, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER | SWP_NOMOVE);

	m_DC = GetDC(m_Hwnd);

	ShowWindow(m_Hwnd, SW_SHOWDEFAULT);
	UpdateWindow(m_Hwnd);

	return TRUE;
}

///////////////////////////////////////////////// Stage

void Util_Core::ChangeStage(ALLSTAGE _Stage)
{
	if (nullptr == m_AllStage[_Stage])
	{
		Tassert(true);
		return;
	}


	// 최초 한번은 nullptr이다. 지정된것이 없기때문
	if (nullptr == m_pCurStage)
	{
		m_pCurStage = m_AllStage[_Stage];

		if (false == m_pCurStage->m_bLoading)
		{
			m_pCurStage->Loading();
			m_pCurStage->m_bLoading = true;
		}
		return;
	}
	else
	{
		m_pNextStage = m_AllStage[_Stage];
		return;
	}
}

