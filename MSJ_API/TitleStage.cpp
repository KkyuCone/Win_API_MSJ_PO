#include "stdafx.h"
#include "TitleStage.h"
#include "Util_Core.h"
#include "ResourceManager.h"
#include "TitleBackground.h"
#include "TitleButton.h"
#include "GameMouseCursor.h"
#include "SoundControl.h"
#include "MainSceneState.h"


//////////////////////////////////////////////////

TitleStage::TitleStage()
{
}


TitleStage::~TitleStage()
{
}

///////////////////////////////////////////////////


void TitleStage::Loading()
{
	// 배경음 넣기
	m_SoundControlBGM->Sound_NewPlay(L"MainSceneBGM.ogg");
	m_SoundControlBGM->Sound_SetPitch(1.0f);

	Create_Actor<TitleBackground>();
	Create_Actor<TitleButton>();
	Create_Actor<GameMouseCursor>();

	Collision_Link(L"Mouse", L"TitleButton");
}


void TitleStage::Start_Update()
{
}

void TitleStage::End_Debug_Update()
{
	wchar_t OutText[100]{};
	swprintf_s(OutText, L"Title Stage");
	TextOutW(BHDC, 20, 0, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"FPS : %d", TimeManager::Instance().FPS());
	TextOutW(BHDC, 20, 20, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"All Obejct Count : %d", AllObjCount());
	TextOutW(BHDC, 20, 40, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"X : %d Y : %d", InputManager::Instance().MousePos().X, InputManager::Instance().MousePos().Y);
	TextOutW(BHDC, 20, 60, OutText, lstrlenW(OutText));
}
