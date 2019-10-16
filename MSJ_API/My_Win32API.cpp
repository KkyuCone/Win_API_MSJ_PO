// My_Win32API.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "My_Win32API.h"
#include "Util_Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	srand((unsigned int)time(0));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return Util_Core::Instance().WinAPI_Start(hInstance);
}

