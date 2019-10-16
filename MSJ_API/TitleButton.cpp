#include "stdafx.h"
#include "TitleButton.h"
#include "Util_Core.h"
#include "SingleRenderer.h"
#include "ObjectCollision.h"
#include "AnimationRenderer.h"


TitleButton::TitleButton() : m_pTitleButton_1P(nullptr), m_pTitleButton_2P(nullptr), m_pTitleButton_Editor(nullptr), m_pTitleButton_Exit(nullptr), m_FadeIn(true)
{
	//CreateWindowW(L"button", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 100, 100, 100, Util_Core::Instance().WINDOW_HWND(),
	//	0, Util_Core::Instance().WINDOW_INSTANCE(), 0);


}


TitleButton::~TitleButton()
{
}


void TitleButton::Start_Update()
{
	// 1P Button
	m_pTitleButton_1P = Create_Renderer<SingleRenderer>(0);
	m_pTitleButton_1P->SettingSprite(L"TitleButton_1P.bmp");
	m_pTitleButton_1P->Size(F_Position{ 100, 100 });
	m_pTitleButton_1P->Pivot(F_Position{ 200, 630});		// 100 480      x-> 100 y -> 150

	ObjectCollision* pButtonCol01 = Create_Collision(L"TitleButton");
	pButtonCol01->Size(F_Position(100, 100));
	pButtonCol01->Pivot(m_pTitleButton_1P->Pivot());
	pButtonCol01->Name = L"1PButton";

	
	// 2P Button
	m_pTitleButton_2P = Create_Renderer<SingleRenderer>(0);
	m_pTitleButton_2P->SettingSprite(L"TitleButton_2P.bmp");
	m_pTitleButton_2P->Size(F_Position{ 100, 100 });
	m_pTitleButton_2P->Pivot(F_Position{ 400, 630 });

	ObjectCollision* pButtonCol02 = Create_Collision(L"TitleButton");
	pButtonCol02->Size(F_Position(100, 100));
	pButtonCol02->Pivot(m_pTitleButton_2P->Pivot());
	pButtonCol02->Name = L"2PButton";


	// MapEditor Button
	m_pTitleButton_Editor = Create_Renderer<SingleRenderer>(0);
	m_pTitleButton_Editor->SettingSprite(L"TitleButton_Editor.bmp");
	m_pTitleButton_Editor->Size(F_Position{ 100, 100 });
	m_pTitleButton_Editor->Pivot(F_Position{ 600, 630 });

	ObjectCollision* pButtonCol03 = Create_Collision(L"TitleButton");
	pButtonCol03->Size(F_Position(100, 100));
	pButtonCol03->Pivot(m_pTitleButton_Editor->Pivot());
	pButtonCol03->Name = L"MapEditorButton";


	// Exit Button
	m_pTitleButton_Exit = Create_Renderer<SingleRenderer>(0);
	m_pTitleButton_Exit->SettingSprite(L"TitleButton_Exit.bmp");
	m_pTitleButton_Exit->Size(F_Position{ 100, 100 });
	m_pTitleButton_Exit->Pivot(F_Position{ 800, 630 });

	ObjectCollision* pButtonCol04 = Create_Collision(L"TitleButton");
	pButtonCol04->Size(F_Position(100, 100));
	pButtonCol04->Pivot(m_pTitleButton_Exit->Pivot());
	pButtonCol04->Name = L"ExitButton";


	//BlackFadeInOut
	m_FadeInRenderer = Create_Renderer<AnimationRenderer>(10);
	//m_FadeInRenderer->SettingSprite(L"BlackFadeInOut.bmp");
	m_FadeInRenderer->Animation_Create(L"FadeIn", L"BlackFadeInOut.bmp", 0,0, false, 0.1f);
	m_FadeInRenderer->Size(F_Position{ 1024, 768 });
	m_FadeInRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });

	m_FadeInRenderer->Animation_Change(L"FadeIn");
}

void TitleButton::Prev_Update()
{

}


void TitleButton::Update()
{
	InputMouseButton();


	if (true == m_FadeIn)
	{
		if (4 >= m_FadeInRenderer->Get_Alpha())
		{
			m_FadeIn = false;
			m_FadeInRenderer->Obj_Death();
		}

		if (255 >= m_FadeInRenderer->Get_Alpha())
		{
			m_FadeInRenderer->Set_Alpha(m_FadeInRenderer->Get_Alpha() - 2);	// 서서히 사라짐
		}
	}
}

void TitleButton::Late_Update()
{

}


//
void TitleButton::InputMouseButton()
{
	//if (150 < InputManager::Instance().MousePos().X && 250 > InputManager::Instance().MousePos().X
	//	&& 580 < InputManager::Instance().MousePos().Y && 680 > InputManager::Instance().MousePos().Y)
	//{
	//	if (true == InputManager::Instance().Down(L"MouseDown"))
	//	{
	//		Util_Core::Instance().ChangeStage(ALLSTAGE::PLAY);
	//	}
	//}
	//else if (350 < InputManager::Instance().MousePos().X && 450 > InputManager::Instance().MousePos().X
	//	&& 580 < InputManager::Instance().MousePos().Y && 680 > InputManager::Instance().MousePos().Y)
	//{

	//}
	//else if (550 < InputManager::Instance().MousePos().X && 650 > InputManager::Instance().MousePos().X
	//	&& 580 < InputManager::Instance().MousePos().Y && 680 > InputManager::Instance().MousePos().Y)
	//{
	//	if (true == InputManager::Instance().Down(L"MouseDown"))
	//	{
	//		Util_Core::Instance().ChangeStage(ALLSTAGE::EDITOR);
	//	}
	//}
	//else if (750 < InputManager::Instance().MousePos().X && 850 > InputManager::Instance().MousePos().X
	//	&& 580 < InputManager::Instance().MousePos().Y && 680 > InputManager::Instance().MousePos().Y)
	//{
	//	// 프로그램 종료하기
	//	if (true == InputManager::Instance().Down(L"MouseDown"))
	//	{
	//		//exit(0);
	//		HWND hwnd = FindWindowW(L"WindowClass", L"Window");
	//		if (hwnd == nullptr)
	//		{
	//			Tassert(true);
	//			return;
	//		}
	//		else
	//		{
	//			DestroyWindow(hwnd);
	//			//exit(0);
	//		}
	//	}
	//}
	//else
	//{
	//	return;
	//}
}
