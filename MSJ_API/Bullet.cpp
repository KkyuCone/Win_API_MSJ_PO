#include "stdafx.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include  "AnimationRenderer.h"
#include "ObjectCollision.h"
#include "SoundControl.h"

///////////////////////////////////////////////////////

Bullet::Bullet() : m_bullet{ {0.0f, 0.0f}, {30.f, 6.0f} }, m_DeathTimer(3.0f)
{
	m_BulletScale = 1.0f;
}


Bullet::~Bullet()
{
}

///////////////////////////////////////////////////////

void Bullet::Start_Update()
{

	m_BulletSize = F_Position{ 30, 30 };

	ObjectCollision* pCol = Create_Collision(L"PlayerBullet");
	pCol->Size(F_Position(20, 20));
	pCol->Name = L"PlayerBullet";


	m_pTestAniRenderer = Create_Renderer<AnimationRenderer>();
	m_pTestAniRenderer->Size(m_BulletSize);
	m_pTestAniRenderer->Animation_Create(L"Test1", L"unit_bazzi.bmp", 0, 4);
	m_pTestAniRenderer->Animation_Change(L"Test1");
}

void Bullet::Prev_Update()
{
}

void Bullet::Update()
{
	m_BulletScale += TimeManager::Instance().DeltaTime();
	ScaleRatio(m_BulletScale);

	m_BasePos += m_bulletDir  * 100.0f * TimeManager::Instance().DeltaTime();


	if (true == m_DeathTimer.TimerCheck())
	{
		Obj_Death();
		m_DeathTimer.TimerReset();
	}
}

void Bullet::Late_Update()
{
	//m_bullet.Position = m_BasePos;
	//Rectangle(BHDC, m_bullet.I_Left(), m_bullet.I_Top(), m_bullet.I_Right(), m_bullet.I_Botton());
}

void Bullet::Other_Collision_Enter(ObjectCollision * _This, ObjectCollision * _Other)
{
	m_bulletDir *= -1;
}

