#include "stdafx.h"
#include "SelectBackground1P.h"
#include "ResourceManager.h"
#include "SingleRenderer.h"
#include "GameObjectImage.h"
#include "AnimationRenderer.h"

////////////////////////////////////////////

SelectBackground1P::SelectBackground1P() : m_FadeIn(true)
{
}


SelectBackground1P::~SelectBackground1P()
{
}

///////////////////////////////////////////

void SelectBackground1P::Start_Update()
{
	SingleRenderer* m_SelectSceneRenderer = Create_Renderer<SingleRenderer>(0);
	m_SelectSceneRenderer->SettingSprite(L"SelectBackground_1P.bmp");
	m_SelectSceneRenderer->Size(F_Position{ 1024, 768 });
	m_SelectSceneRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });


	m_FadeInRenderer = Create_Renderer<AnimationRenderer>(10);
	m_FadeInRenderer->Animation_Create(L"FadeIn", L"BlackFadeInOut.bmp", 0, 0, false, 0.1f);
	m_FadeInRenderer->Size(F_Position{ 1024, 768 });
	m_FadeInRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });

	m_FadeInRenderer->Animation_Change(L"FadeIn");

}

void SelectBackground1P::Update()
{
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
