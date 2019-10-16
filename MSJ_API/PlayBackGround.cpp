#include "stdafx.h"
#include "PlayBackGround.h"
#include "SingleRenderer.h"
#include "ObjectCollision.h"
#include "AnimationRenderer.h"


PlayBackGround::PlayBackGround() : m_FadeIn(true)
{
}


PlayBackGround::~PlayBackGround()
{
}


void PlayBackGround::Start_Update()
{
	SingleRenderer* m_pTitleRenderer = Create_Renderer<SingleRenderer>(0);
	m_pTitleRenderer->SettingSprite(L"InGame.bmp");
	m_pTitleRenderer->Size(F_Position{ 1024, 768 });
	m_pTitleRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });



	ObjectCollision* pLimitUp = Create_Collision(L"Limit_Up");
	pLimitUp->Name = L"Limit_Up";
	pLimitUp->Pivot(F_Position(1024 / 2, 25));
	pLimitUp->Size(F_Position(1024, 50));

	ObjectCollision* pLimitLeft = Create_Collision(L"Limit_Left");
	pLimitLeft->Name = L"Limit_Left";
	pLimitLeft->Pivot(F_Position(-1, 768 / 2));
	pLimitLeft->Size(F_Position(50, 768));

	ObjectCollision* pLimitRight = Create_Collision(L"Limit_Right");
	pLimitRight->Name = L"Limit_Right";
	pLimitRight->Pivot(F_Position(820, 768 / 2));
	pLimitRight->Size(F_Position(50, 768));

	ObjectCollision* pLimitDown = Create_Collision(L"Limit_Down");
	pLimitDown->Name = L"Limit_Down";
	pLimitDown->Pivot(F_Position(1024 / 2 , 744));
	pLimitDown->Size(F_Position(1024, 50));

	m_FadeInRenderer = Create_Renderer<AnimationRenderer>(20);
	m_FadeInRenderer->Animation_Create(L"FadeIn", L"BlackFadeInOut.bmp", 0, 0, false, 0.1f);
	m_FadeInRenderer->Size(F_Position{ 1024, 768 });
	m_FadeInRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });

	m_FadeInRenderer->Animation_Change(L"FadeIn");
}


// 충돌체 렌더 보여주기
void PlayBackGround::DebugRender()
{

}

void PlayBackGround::Update()
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