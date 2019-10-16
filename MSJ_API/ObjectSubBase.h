#pragma once
#include "ObjUpdateBase.h"

class ActorObjBase;
class ObjectSubBase : public ObjUpdateBase
{
public:
	friend ActorObjBase;

public:
	// 부모님의 위치, 플레이어 or 몬스터의 위치를 알고 싶음
	ActorObjBase* m_pObject;

private:
	void Object(ActorObjBase* _pObj)
	{
		m_pObject = _pObj;
	}

public:
	ActorObjBase* Object() const
	{
		return m_pObject;
	}

public:
	bool IsObjDeath() override;
	bool IsObjUpdate() override;

protected:
	F_Position m_Size;
	F_Position m_Pivot;

public:
	F_Position Size()
	{
		return m_Size;
	}

	F_Position Pivot()
	{
		return m_Pivot;
	}

	void Size(F_Position _Size)
	{
		m_Size = _Size;
	}

	void Pivot(F_Position _Pivot)
	{
		m_Pivot = _Pivot;
	}

public:
	F_Position ParentPos();
	F_Position ScreenPos();

public:
	ObjectSubBase();
	~ObjectSubBase();
};

