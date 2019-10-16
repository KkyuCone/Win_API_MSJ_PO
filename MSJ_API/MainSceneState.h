#pragma once
#include <list>
#include <map>
#include <string>
#include "RenderManager.h"
#include "CollisionManager.h"

class Util_Core;
class ActorObjBase;
class ObjectRenderer;
class CollisionManager;
class SoundControl;
class MainSceneState
{
public:
	friend Util_Core;
	friend ActorObjBase;

public:
	static 	SoundControl* m_SoundControlBGM;

	// 맵이름
public:
	static std::wstring SelectMapName;
	
private:
	std::list<ActorObjBase*>::iterator m_ObjStart;
	std::list<ActorObjBase*>::iterator m_ObjEnd;
	std::list<ActorObjBase*> m_ObjList;
	bool m_bLoading;

	F_Position m_Camera;


public:
	enum CharacterType
	{
		Bazzi,
		Dao,
		Marid,
		Cappy
	};

public:
	static CharacterType m_GameChar_Type;		// 캐릭터타입



	// 디버그

private:
	static bool IsDebugMode;
	static bool IsDebugColMode;

public:
	static bool IsDebug()
	{
		return IsDebugMode;
	}

	static void DebugMode_On()
	{
		IsDebugMode = true;
	}

	static void DebugMode_Off()
	{
		IsDebugMode = false;
	}

	static void DebugCol_On()
	{
		IsDebugColMode = true;
	}

	static void DebugCol_Off()
	{
		IsDebugColMode = false;
	}

public:

	// 카메라이동할때 같이 이동하려고
	void MovePos(F_Position _Pos)
	{
		m_Camera += _Pos;
	}

	void CameraPos(F_Position _CameraPos)
	{
		m_Camera = _CameraPos;
	}

	F_Position CameraPos()
	{
		return m_Camera;
	}


protected:
	MainSceneState();
	virtual ~MainSceneState();

public:
	size_t AllObjCount()
	{
		return m_ObjList.size();
	}

private:
	virtual void Change_Scene_Start() {}  // 화면에 보이기로 한 씬이 한번 실행한다.
	virtual void Start_Update() {}  // 이번에 변경된 녀석이 한번 실행해준다.
	virtual void End_Debug_Update() {}
	virtual void Change_Scene_End() {}  // 이번에 변경된 녀석이 한번 실행해준다.

private:
	virtual void Loading() = 0;

	void Prev_Update();
	void Update();
	void Late_Update();

	void Obj_Render();			// Render

	void Obj_Collision();

	void Release();

public:
	template<typename T>
	T* Create_Actor()
	{
		T* NewActorObj = new T();
		NewActorObj->Stage(this);
		NewActorObj->Start_Update();
		m_ObjList.push_back(NewActorObj);
		return (T*)NewActorObj;
	}

//////////////////////////////////////// Render
private:
	RenderManager m_RenderManager;

private:
	void Obj_Renderer_Insert(int _Key, ObjectRenderer* _pObjRenderer);

public:
	void YSort_On(int _YValue);


////////////////////////////////////////// Collision
private:
	CollisionManager m_ColManager;

private:
	void Insert_Collision(const wchar_t* _GroupName, ObjectCollision* _pObjCollision);

protected:
	void Collision_Link(const wchar_t* _Left, const wchar_t* _Right);
	void Collision_LinkOverlap(const wchar_t * _Left, const wchar_t * _Right);
};



