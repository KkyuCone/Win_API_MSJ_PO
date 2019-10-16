#include "stdafx.h"
#include "Player.h"
#include "AnimationRenderer.h"
#include <string>
#include "InGameTimer.h"

void Player::Idle()
{
	if (true == InputManager::Instance().DownStay(L"Left")
		|| true == InputManager::Instance().DownStay(L"Right")
		|| true == InputManager::Instance().DownStay(L"Up")
		|| true == InputManager::Instance().DownStay(L"Down"))
	{
		Player_ChangeState(RUN);
	}

	if (true == InputManager::Instance().DownStay(L"PrevAni"))
	{
		Player_ChangeState(ATTACK);
	}
}

void Player::Run()
{
	Move();

	if (false == InputManager::Instance().DownStay(L"Left")
		&& false == InputManager::Instance().DownStay(L"Right")
		&& false == InputManager::Instance().DownStay(L"Up")
		&& false == InputManager::Instance().DownStay(L"Down"))
	{
		Player_ChangeState(IDLE);
	}

	if (true == InputManager::Instance().DownStay(L"PrevAni"))
	{
		Player_ChangeState(ATTACK);
	}
}

void Player::Attack()
{
	if (true == m_pTestAniRenderer->IsEndAnimation())
	{
		Player_ChangeState(IDLE);
	}
}

void Player::Bubble_First()
{
	// 바늘 사용시 터트리기
	if (true == InputManager::Instance().Down(L"Ctrl"))
	{
		int a = 0;

		std::wstring ItemName = UseItem();
		if (ItemName == L"Needle_Get")
		{
			m_GetItem.clear();						// 사용한 아이템 제거
			Player_ChangeState(BubblePop, false);
			return;
		}
	}

	if (true == m_pTestAniRenderer->IsEndAnimation(L"Death_01"))
	{
		int a = 0;
		m_pTestAniRenderer->Animation_Change(L"Death_02");
		Player_ChangeState(Death_02, false);
	}
}

void Player::Bubble_Second()
{
	// 바늘 사용시 터트리기
	if (true == InputManager::Instance().Down(L"Ctrl"))
	{
		std::wstring ItemName = UseItem();
		int a = 0;
		if (ItemName == L"Needle_Get")
		{
			m_GetItem.clear();						// 사용한 아이템 제거
			Player_ChangeState(BubblePop, false);
			return;
		}
	}

	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_02"))
	{
		if (true == m_BombTimer.TimerCheck())
		{
			m_pTestAniRenderer->Animation_Change(L"Death_03");
			m_BombTimer.TimerReset();
			Player_ChangeState(Death_03, false);
		}
	}
}

void Player::Bubble_Third()
{
	if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_03"))
	{
		if (true == m_DeathTimer.TimerCheck())
		{
			m_bDeath = true;
			m_pTestAniRenderer->Animation_Change(L"Death_End");
			Player_ChangeState(Death_End, false);

			m_DeathTimer.TimerReset();

			if (false == m_InGameTimer->Get_m_BalckEmtpy())
			{
				m_InGameTimer->BalckEmtpyValueChange(true);		// Lose관련
				m_InGameTimer->Sound_Lose();					// Lose 관련
			}

		}
	}
}

void Player::Death()
{

}

void Player::Bubble_Pop()
{
	//if (true == m_pTestAniRenderer->IsCurAnimation(L"BubblePop"))

	if (true == m_pTestAniRenderer->IsEndAnimation())
	{
		m_bIsBubble = false;
		Player_ChangeState(IDLE);
	}
}