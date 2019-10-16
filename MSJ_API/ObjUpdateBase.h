#pragma once
class ObjUpdateBase
{
private:
	bool m_bDeath;
	bool m_bUpdate;

public:
	void On()
	{
		m_bUpdate = true;
	}

	void Off()
	{
		m_bUpdate = false;
	}

	// 오브젝트 사망, 삭제
	void Obj_Death()
	{
		m_bDeath = true;
	}

	void Obj_Save()
	{
		m_bDeath = false;
	}


public:
	virtual bool IsObjDeath()
	{
		return true == m_bDeath;
	}

	virtual bool IsObjUpdate()
	{
		return true == m_bUpdate && false == m_bDeath;
	}
public:
	ObjUpdateBase();
	virtual ~ObjUpdateBase();
};

