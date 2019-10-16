#pragma once
#include <vector>
#include "Render_Vector.h"

enum ALLSTAGE
{
	TITLE,
	GAMESELECT,
	GAMESELECT_2P,
	PLAY,
	PLAY_2P,
	EDITOR,
	INVENTORY,
	STORE,
	MAX,
};

class MainSceneState;
class Util_Core
{
public:
	// Util_Core 싱글톤
	static Util_Core& Instance()
	{
		static Util_Core UtilCore = Util_Core();
		return UtilCore;
	}

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private:
	// 멤버 변수
	static bool m_UtilCore_Life;
	HINSTANCE m_hInstance;
	HWND m_Hwnd;
	HDC m_DC;
	I_Size m_SceneSize;

public:
	Util_Core();
	~Util_Core();

public:
	HINSTANCE WINDOW_INSTANCE()
	{
		return m_hInstance;
	}

	HDC WINDOW_DC()
	{
		return m_DC;
	}

	HWND WINDOW_HWND()
	{
		return m_Hwnd;
	}

	I_Size WINDOWN_SIZE()
	{
		return m_SceneSize;
	}

	void Change_SceneSize(int _width, int _height)
	{
		m_SceneSize.X = _width;
		m_SceneSize.Y = _height;
	}

private:
	ATOM                MyRegisterClass(HINSTANCE hInstance);		// 윈도우창 클래스
	BOOL                InitInstance(HINSTANCE);

private:
	void UserInit();
	void Progress();

public:
	template<typename T>
	T* Create_Stage(ALLSTAGE _Stage)
	{
		m_AllStage[_Stage] = new T();
		return (T*)m_AllStage[_Stage];
	}

public:
	int WinAPI_Start(HINSTANCE _hInstance);


///////////////////////////////////////////////// Stage
private:
	// state패턴
	std::vector<MainSceneState*> m_AllStage;
	MainSceneState* m_pCurStage;
	MainSceneState* m_pNextStage;

public:
	void ChangeStage(ALLSTAGE _Stage);
};

