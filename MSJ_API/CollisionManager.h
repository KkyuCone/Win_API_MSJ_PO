#pragma once
#include <map>
#include <set>
#include <list>

// �׷� ������

// 1.�ڱ� �ڽŰ� �浹 ����
// 2. �ٸ� �׷�� �浹����
//   -> n�� �̻��� �׷�� �浹�� �� �ִ�.
//		�÷��̾� �Ѿ�, ����, ���� �Ѿ�

class MainSceneState;
class ObjectCollision;
class CollisionManager
{
private:
	friend MainSceneState;

private:
	// ex ) ���� �浹
	//		���� -> ����, �÷��̾� �Ѿ�
	//		�÷��̾� -> ���� �Ѿ�

	class CollisionCroup
	{
	private:
		friend CollisionManager;
		std::wstring Name;

	private:
		std::list<ObjectCollision*>::iterator m_ThisStartIter;
		std::list<ObjectCollision*>::iterator m_ThisEndIter;

		std::list<ObjectCollision*>::iterator m_OtherStartIter;
		std::list<ObjectCollision*>::iterator m_OtherEndIter;

		std::list<ObjectCollision*> m_ObjColList;

		//////////////////

		std::list<CollisionCroup*>::iterator m_OtherStart;
		std::list<CollisionCroup*>::iterator m_OtherEnd;

		std::list<CollisionCroup*> m_OtherColGroup;

	public:
		void Link(CollisionCroup* _OtherGroup);
		void LinkOverlap(CollisionCroup* _OtherGroup);
		void Insert_Collision(ObjectCollision* _ObjCol);
		void Collision_Check(CollisionCroup* _OtherGroup);
		void Collision_Update();
		
		void Collision_Setting();
		void Release();

		void DebugRender();

	private:
		CollisionCroup();
		~CollisionCroup();
	};

private:
	std::map<std::wstring, CollisionCroup*>::iterator m_FindGroupIter;
	std::map<std::wstring, CollisionCroup*> m_ColGroupMap;

private:
	CollisionCroup* FindColGroup(const wchar_t* _GroupName);

public:
	void Insert_Collision(const wchar_t* _GroupName, ObjectCollision* _ObjCol);
	void Link(const wchar_t* _Left, const wchar_t* _Right);
	void LinkOverlap(const wchar_t* _Left, const wchar_t* _Right);

	void Collision_Update();
	void Release();

	void DebugRender();

public:
	CollisionManager();
	~CollisionManager();
};

