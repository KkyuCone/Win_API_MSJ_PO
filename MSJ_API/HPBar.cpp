#include "stdafx.h"
#include "HPBar.h"
#include "SingleRenderer.h"
#include "ResourceManager.h"
#include "MainSceneState.h"

HPBar::HPBar() : m_BarBackground(nullptr), m_HPImage(nullptr), ShotValue(0)
{
}


HPBar::~HPBar()
{
}

//////////////////////////////////

void HPBar::Init(ActorObjBase* _Actor, int* _hp, int _MaxHP, F_Position _Size)
{
	m_HP = _hp;
	m_HPMax = _MaxHP;

	m_BarBackground = _Actor->Create_Renderer<SingleRenderer>(15);
	m_BarBackground->Size(_Size);
	m_BarBackground->SettingSprite(L"HpBack.bmp");
	//m_BarBackground->Pivot(F_Position{ 0, 400 });
	m_BarBackground->ParentPos() = _Actor->Pos();
	m_BarBackground->Pivot(F_Position{ 0, -32 });

	m_HPImage = _Actor->Create_Renderer<SingleRenderer>(16);
	m_HPImage->Size(_Size);
	m_HPImage->SettingSprite(L"HpBar.bmp");
	//m_HPImage->Pivot(F_Position{ 0, 400 });
	m_HPImage->ParentPos() = _Actor->Pos();
	m_HPImage->Pivot(F_Position{ 0, -32 });

	

	//m_HPImage->Size({ _Size.X * 500 / _MaxHP, _Size.Y });

	ActorHPSize = m_HPImage->Size();
	m_HPImage->Size({ ActorHPSize.X * 500 / m_HPMax, ActorHPSize.Y });

}

void HPBar::Damage()
{
	if (ActorHPSize.X * 500 / m_HPMax > 0)
	{
		++ShotValue;
	}

	ActorHPSize -= F_Position{ 20, 0 };
	m_HPImage->Pivot(F_Position{ -10 * ShotValue, -32 });
	m_HPImage->Size({ ActorHPSize.X * 500 / m_HPMax, ActorHPSize.Y });
}

bool HPBar::Death()
{
	if (ActorHPSize.X * 500 / m_HPMax > 0)
	{
		return false;
	}

	return true;
}