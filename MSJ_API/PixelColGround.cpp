#include "stdafx.h"
#include "PixelColGround.h"
#include "SingleRenderer.h"
#include "AnimationRenderer.h"
#include "ObjectCollision.h"

///////////////////////////////////////////////////
PixelColGround::PixelColGround() : m_ExitAniRenderer(nullptr), m_ExitButtonCol(nullptr)
{
}


PixelColGround::~PixelColGround()
{
}

/////////////////////////////////////////////////////

void PixelColGround::Start_Update()
{
	SingleRenderer* m_pTestAniRenderer = Create_Renderer<SingleRenderer>();
	m_pTestAniRenderer->SettingSprite(L"BackGround_Col.bmp");
	m_pTestAniRenderer->Size(F_Position{ 1024, 768 });
	m_pTestAniRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });

	// 나가기 버튼
	m_ExitAniRenderer = Create_Renderer<AnimationRenderer>(13);
	m_ExitAniRenderer->Size(F_Position{ 200, 49 });
	m_ExitAniRenderer->Pivot(F_Position{ 918, 738 });
	m_ExitAniRenderer->Animation_Create(L"InGame_ExitButton", L"InGame_ExitButton.bmp", 0, 0, false);
	m_ExitAniRenderer->Animation_Create(L"InGame_ExitButtonClick", L"InGame_ExitButton.bmp", 1, 1, false);

	m_ExitAniRenderer->Animation_Change(L"InGame_ExitButton");


	m_ExitButtonCol = Create_Collision(L"InGameExitButton");
	m_ExitButtonCol->Size(F_Position{ 200, 49 });
	m_ExitButtonCol->Pivot(F_Position{ 918, 738 });
	m_ExitButtonCol->Name = L"ExitButton";
}

void PixelColGround::GameExit(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (true == InputManager::Instance().Down(L"MouseDown"))
	{
		if (_Other->Name == L"MouseCursor")
		{
			// 프로그램 종료하기
			if (true == InputManager::Instance().Down(L"MouseDown"))
			{
				HWND hwnd = FindWindowW(L"WindowClass", L"Window");
				if (hwnd == nullptr)
				{
					Tassert(true);
					return;
				}
				else
				{
					DestroyWindow(hwnd);
				}
			}
		}
	}
}




void PixelColGround::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	int a = 0;
	if (_This->Name == L"ExitButton" && _Other->Name == L"MouseCursor")
	{
		m_ExitAniRenderer->Animation_Change(L"InGame_ExitButtonClick");
	}
}

void PixelColGround::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_This->Name == L"ExitButton" && _Other->Name == L"MouseCursor")
	{
		GameExit(_This, _Other);
	}
}

void PixelColGround::Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_This->Name == L"ExitButton")
	{
		m_ExitAniRenderer->Animation_Change(L"InGame_ExitButton");
	}
}