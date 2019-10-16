#include "stdafx.h"
#include "GameMouseCursor.h"
#include "Util_Core.h"
#include "SingleRenderer.h"
#include "ObjectCollision.h"
#include "SoundControl.h"
#include "ResourceManager.h"

GameMouseCursor::GameMouseCursor() : m_MouseCursor(nullptr)
{
}


GameMouseCursor::~GameMouseCursor()
{
}


/////////////////////////////////////////////////////
//

void GameMouseCursor::Start_Update()
{
	m_SoundControl = ResourceManager::Instance().SoundControl_Insert();

	m_MouseCursor = Create_Renderer<SingleRenderer>(15);
	m_MouseCursor->SettingSprite(L"MouseCursor_None.bmp");
	m_MouseCursor->Size(F_Position{ 35, 38 });
	//m_MouseCursor->Pivot(F_Position{ InputManager::Instance().MousePos_F().X, InputManager::Instance().MousePos_F().Y });		// 100 480      x-> 100 y -> 150
	m_MouseCursor->Pivot({ MOUSEXVALUE , MOUSEYVALUE});

	m_pMouseCol = Create_Collision(L"Mouse");
	m_pMouseCol->Size(F_Position(5, 5));
	m_pMouseCol->Pivot(m_MouseCursor->Pivot() + F_Position{ -MOUSEXCOLVALUE, -MOUSECOLYVALUE });
	m_pMouseCol->Name = L"MouseCursor";
}


void GameMouseCursor::Update()
{
	MouseMove();
	MouseState();

}


// 충돌

void GameMouseCursor::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{
	MouseClick(_This, _Other);
}


//
void GameMouseCursor::MouseMove()
{
	m_MouseCursor->Pivot(F_Position{ InputManager::Instance().MousePos_F().X + MOUSEXVALUE, InputManager::Instance().MousePos_F().Y + MOUSEYVALUE });
	m_pMouseCol->Pivot(m_MouseCursor->Pivot() + F_Position{ -MOUSEXCOLVALUE, -MOUSECOLYVALUE });
}

void GameMouseCursor::MouseState()
{
	if (true == InputManager::Instance().DownStay(L"MouseDown"))
	{
		m_MouseCursor->SettingSprite(L"MouseCursor_Click.bmp");
	}
	else
	{
		m_MouseCursor->SettingSprite(L"MouseCursor_None.bmp");
	}
}

void GameMouseCursor::MouseClick(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (true == InputManager::Instance().Down(L"MouseDown"))
	{
		m_MouseCursor->SettingSprite(L"MouseCursor_Click.bmp");

		// 타이틀
		if (_Other->Name == L"1PButton")
		{
			//Util_Core::Instance().ChangeStage(ALLSTAGE::PLAY);  GAMESELECT
			Util_Core::Instance().ChangeStage(ALLSTAGE::GAMESELECT);

			m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
			m_SoundControl->Sound_SetPitch(1.0f);
		}
		else if (_Other->Name == L"2PButton")
		{
			m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
			m_SoundControl->Sound_SetPitch(1.0f);
		}
		else if (_Other->Name == L"MapEditorButton")
		{
			Util_Core::Instance().ChangeStage(ALLSTAGE::EDITOR);

			m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
			m_SoundControl->Sound_SetPitch(1.0f);
		}
		else if (_Other->Name == L"ExitButton")
		{
			// 프로그램 종료하기
			if (true == InputManager::Instance().Down(L"MouseDown"))
			{
				m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
				m_SoundControl->Sound_SetPitch(1.0f);

				//exit(0);
				HWND hwnd = FindWindowW(L"WindowClass", L"Window");
				if (hwnd == nullptr)
				{
					Tassert(true);
					return;
				}
				else
				{
					DestroyWindow(hwnd);
					//exit(0);
				}
			}
		}

	}
}


