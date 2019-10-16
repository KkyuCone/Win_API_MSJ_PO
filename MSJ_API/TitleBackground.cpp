#include "stdafx.h"
#include "TitleBackground.h"
#include "ResourceManager.h"
#include "SingleRenderer.h"
#include "GameObjectImage.h"

//////////////////////////////////////////////////
TitleBackground::TitleBackground()
{
}


TitleBackground::~TitleBackground()
{
}

//////////////////////////////////////////////////


void TitleBackground::Start_Update()
{
	//Rectangle(BHDC, 0, 0, 1024, 768);

	SingleRenderer* m_pTitleRenderer = Create_Renderer<SingleRenderer>(0);
	m_pTitleRenderer->SettingSprite(L"Title_Background.bmp");
	m_pTitleRenderer->Size(F_Position{ 1024, 768 });
	m_pTitleRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });
}

void TitleBackground::Update()
{

}


void TitleBackground::Late_Update()
{
	//Rectangle(BHDC, 0, 0, 1024, 768);
}

