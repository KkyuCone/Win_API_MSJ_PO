#include "stdafx.h"
#include "Monster.h"
#include "AnimationRenderer.h"
#include "ObjectCollision.h"
#include "InGameTimer.h"

void Monster::Idle()
{
	if (true == m_bAttack)
	{
		if (true == m_AttackTime.TimerCheck())
		{
			Monster_ChangeState(ATTACK);
			m_AttackTime.TimerReset();
		}
	}
	else
	{
		int  a = 0;
		if (true == m_WaitIdleTime.TimerCheck())
		{
			RandomAttackValue();
			Monster_ChangeState(RUN);
			m_WaitIdleTime.TimerReset();
		}
	}
}

void Monster::Run()
{

	//if (true == m_Shot)
	//{
	//	if (true == m_ShotTimer.TimerCheck())
	//	{
	//		m_ShotTimer.TimerReset();
	//		m_Shot = false;
	//	}
	//}

	if (true == m_RunToChangeTime.TimerCheck())
	{
		if (true == m_bAttack)
		{
			Monster_ChangeState(ATTACK);
		}
		//else
		//{
		//	Monster_ChangeState(IDLE);
		//}
		m_RunToChangeTime.TimerReset();
	}
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

void Monster::Attack()
{
	if (true == m_AttackTime.TimerCheck())
	{
		m_AttackTime.TimerReset();
		Monster_ChangeState(RUN);
		return;
	}

	if (true == m_bAttack)
	{
		m_bAttack = false;
		int AttackPattern = rand() % 2;

		switch (AttackPattern)
		{
		case 0:
			BubbleAttack(3, pObjCol->ParentPos());
			break;
		case 1:
			BubbleAttack(3, pObjCol->ParentPos());
			BubbleAttack(4, pObjCol->ParentPos());
			break;
		default:
			break;
		}

		return;
	}

	if (false == m_pTestAniRenderer->IsCurAnimation(L"UAttack") &&
		false == m_pTestAniRenderer->IsCurAnimation(L"DAttack") &&
		false == m_pTestAniRenderer->IsCurAnimation(L"RAttack") &&
		false == m_pTestAniRenderer->IsCurAnimation(L"LAttack"))
	{
		std::wstring Ani_Name = Direction + AnimName[m_MonsterState];
		m_pTestAniRenderer->Animation_Change(Ani_Name.c_str());
	}

}

void Monster::Damage()
{
	if (m_Shot == true)
	{
		if (true == m_ShotTimer.TimerCheck())
		{
			m_Shot = false;
			m_ShotTimer.TimerReset();
			Monster_ChangeState(RUN);
		}
		return;
	}

	if (m_pTestAniRenderer->IsCurAnimation(L"UDamage") || m_pTestAniRenderer->IsCurAnimation(L"DDamage")||
		m_pTestAniRenderer->IsCurAnimation(L"LDamage") || m_pTestAniRenderer->IsCurAnimation(L"RDamage"))
	{
		return;
	}

	// 방향가져오기
	std::wstring CheckDir = Get_Dir();

	if (CheckDir == L"U")
	{
		m_Shot = true;
		m_pTestAniRenderer->Animation_Change(L"UDamage");
		m_HPBar.Damage();
	}
	else if (CheckDir == L"D")
	{
		m_Shot = true;
		m_pTestAniRenderer->Animation_Change(L"DDamage");
		m_HPBar.Damage();
	}
	else if (CheckDir == L"L")
	{
		m_Shot = true;
		m_pTestAniRenderer->Animation_Change(L"LDamage");
		m_HPBar.Damage();
	}
	else if (CheckDir == L"R")
	{
		m_Shot = true;
		m_pTestAniRenderer->Animation_Change(L"RDamage");
		m_HPBar.Damage();
	}
	else
	{
		return;
	}
}

void Monster::Bubble_First()
{
	if (true == m_pTestAniRenderer->IsEndAnimation(L"Death_01"))
	{
		Monster_ChangeState(Death_02);
	}

	if (m_MonsterBubble == true)
		return;

	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_01"))
		return;

	m_pTestAniRenderer->Animation_Change(L"Death_01");
	m_MonsterBubble = true;
}

void Monster::Bubble_Second()
{
	int a = 0;
	if (true == m_BubbleSecondTimer.TimerCheck())
	{
		m_BubbleSecondTimer.TimerReset();
		Monster_ChangeState(Death_03);
	}


	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_02"))
		return;

	m_pTestAniRenderer->Animation_Change(L"Death_02");
}

void Monster::Bubble_Third()
{
	if (true == m_pTestAniRenderer->IsEndAnimation(L"Death_03"))
	{
		Monster_ChangeState(Death_End);

		if (false == m_InGameTimer->Get_m_BalckEmtpy())
		{
			m_InGameTimer->BalckEmtpyValueChange(true);		// Lose관련
			m_InGameTimer->Sound_Win();					// Lose 관련
		}

	}

	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_03"))
		return;

	m_pTestAniRenderer->Animation_Change(L"Death_03");
}

void Monster::Death()
{
	if (true == m_DeathTimer.TimerCheck())
	{
		m_DeathTimer.TimerReset();
		Obj_Death();
		return;
	}

	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_End"))
		return;

	m_pTestAniRenderer->Animation_Change(L"Death_End");
}

void Monster::Test()
{

}