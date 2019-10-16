#pragma once
#include "ActorObjBase.h"
#include "TimerCal.h"

class AnimationRenderer;
class Bullet : public ActorObjBase
{
public:
	friend class MainSceneState;

private:
	F_Rectangle m_bullet;
	F_Position m_bulletDir;		// πÊ«‚

	TimerCal m_DeathTimer;

	AnimationRenderer* m_pTestAniRenderer;
	F_Position m_BulletSize;
	float m_BulletScale;

public:
	void Dir_Change(F_Position _Dir)
	{
		m_bulletDir = _Dir;
	}

private:
	Bullet();
	~Bullet();

private:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;

	void Other_Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;

};

