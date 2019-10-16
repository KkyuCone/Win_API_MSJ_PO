#pragma once
#include "ActorObjBase.h"

class SingleRenderer;
class MainSceneState;
class HPBar 
{
public:
	friend MainSceneState;

public:
	HPBar();
	~HPBar();

private:
	SingleRenderer* m_BarBackground;
	SingleRenderer* m_HPImage;
	ActorObjBase* m_Actor;
	int* m_HP;
	int m_HPMax;
	int ShotValue;
	F_Position ActorHPSize;

public:
	void Init(ActorObjBase* _Actor, int* _hp, int _MaxHP, F_Position _Size);
	void Damage();
	bool Death();

};

