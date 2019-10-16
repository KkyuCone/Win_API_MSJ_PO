#pragma once
#include "ObjNameBase.h"
#include "Render_Vector.h"
#include "MainSceneState.h"

#include <list>

class MainSceneState;
class ObjectRenderer;
class ActorObjBase : public ObjNameBase
{
private:
	friend MainSceneState;

private:
	MainSceneState* m_pStage;


protected:
	ActorObjBase();
	virtual ~ActorObjBase();

	////////////////////////////////////////

private:
	void Stage(MainSceneState* _Stage)
	{
		m_pStage = _Stage;
	}

public:
	MainSceneState* Stage()
	{
		return m_pStage;
	}


	////////////////////////////////////////
protected:
	F_Position m_BasePos;
	float m_ScaleRatio;

public:
	float ScaleRatio()
	{
		return m_ScaleRatio;
	}

	void ScaleRatio(float _ScaleRatio)
	{
		m_ScaleRatio = _ScaleRatio;
	}

public:

	F_Position Pos() const
	{
		return m_BasePos;
	}

	inline void Pos(const F_Position& _Pos)
	{
		m_BasePos = _Pos;
	}

	inline void MovePos(const F_Position& _MovePos)
	{
		m_BasePos += _MovePos;
	}

	F_Position ScreenPos();

public:
	virtual void Start_Update() = 0;
	virtual void Prev_Update();
	virtual void Update();
	virtual void Late_Update();

	virtual void DebugRender();

///////////////////////////////////////////// Render
private:
	std::list<ObjectRenderer*> m_pObjectRendererList;

public:

	// ���� �Ŵ���
	// ������
	// ������ ��ӹ޴� �̱� ������
	// ������ ��ӹ޴� �ִ� ������
	// �׿ܿ� �װ��� �������ֱ� ����
	// ���Ϳ� ������Ʈ�� �����Լ������.

	// 1. �÷��̾ ��������� 
	// 2. -> �÷��̾��� ��ŸƮ���� �������� �����
	// 3. -> ������� �������� ������Ʈ�� �־��ְ�
	// 4. -> ������Ʈ�� �ڽ��� ���� ���� �Ŵ����� �� �������� �־��ְ�
	// 5. -> �������� �����鼭 ��� �������� ������ ȣ�����ִ� �����̴�.

	template <typename T>
	T* Create_Renderer(int _Key = 0)
	{
		T* NewRenderer = new T();
		NewRenderer->Object(this);
		m_pObjectRendererList.push_back(NewRenderer);
		Stage()->Obj_Renderer_Insert(_Key, NewRenderer);


		return NewRenderer;
	}


/////////////////////////////////////////////////// �浹
private:
	std::list<ObjectCollision*> m_pCollisionList;

public:
	ObjectCollision* Create_Collision(const wchar_t* _GroupName, int _Type = 0);

public:
	virtual void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)	{}
	virtual void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) {}
	virtual void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) {}

	virtual void Other_Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) {}
	virtual void Other_Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) {}
	virtual void Other_Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) {}


};

