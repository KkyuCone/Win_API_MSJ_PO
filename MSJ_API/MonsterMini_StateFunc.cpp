#include "stdafx.h"
#include "MonsterMini.h"
#include "AnimationRenderer.h"
#include "ObjectCollision.h"
#include "InGameTimer.h"

void MonsterMini::Idle()
{
}

void MonsterMini::Run()
{
	RandomAttackValue();

	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_01") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"UDamage") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"DDamage") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"LDamage") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"RDamage") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"UAttack") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"DAttack") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"LAttack") ||
		true == m_pTestAniRenderer->IsCurAnimation(L"RAttack"))
	{
		std::wstring Ani_Name = Direction + AnimName[m_MonsterState];
		m_pTestAniRenderer->Animation_Change(Ani_Name.c_str());
	}


	Move();			// 이동 (달리기)
}


void MonsterMini::Damage()
{
}

void MonsterMini::Bubble_First()
{
	if (true == m_pTestAniRenderer->IsEndAnimation(L"Death_01"))
	{
		Obj_Death();
	}
}