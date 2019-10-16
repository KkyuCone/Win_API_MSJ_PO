#pragma once
#include <map>
#include <set>
#include <list>

class ObjectRenderer;
class RenderManager
{
public:
	friend MainSceneState;

private:
	std::map<int, std::list<ObjectRenderer*>>::iterator Start_MapIter;
	std::map<int, std::list<ObjectRenderer*>>::iterator End_MapIter;

	std::list<ObjectRenderer*>::iterator Start_ListIter;
	std::list<ObjectRenderer*>::iterator End_ListIter;

	std::map<int, std::list<ObjectRenderer*>> m_Render;

	// y소팅
	std::set<int>::iterator m_YIter;
	std::set<int> m_YSet;		// set은 key값만 갖고 있는 맵과 같음

private:
	void Renderer_Insert(int _Key, ObjectRenderer* _ObjRenderer);
	void Render();
	void Release();

public:
	void YSort_On(int _idx);

private:
	RenderManager();
	~RenderManager();
};

