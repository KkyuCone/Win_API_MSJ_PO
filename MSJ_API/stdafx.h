// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
//#include <crtdbg.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "InputManager.h"
#include "TimeManager.h"

#define MHDC Util_Core::Instance().WINDOW_DC()
#define BHDC ResourceManager::Instance().BackBufferDC()

#define MOUSEXVALUE 3
#define MOUSEYVALUE 10

#define MOUSEXCOLVALUE 10
#define MOUSECOLYVALUE 15

#define RUZZI_INIT 0
#define BUBBLECOUNT_INIT 1
#define WATERPOWER_INIT 1
#define SPEED_INIT 30

