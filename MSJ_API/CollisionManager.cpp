#include "stdafx.h"
#include "CollisionManager.h"
#include "ObjectCollision.h"

////// CollisionCroup Ŭ����

CollisionManager::CollisionCroup::CollisionCroup()
{

}
CollisionManager::CollisionCroup::~CollisionCroup()
{

}


void CollisionManager::CollisionCroup::Link(CollisionCroup* _OtherGroup)
{
	m_OtherStart = m_OtherColGroup.begin();
	m_OtherEnd = m_OtherColGroup.end();

	for ( ; m_OtherStart != m_OtherEnd; ++m_OtherStart)
	{
		// ������ ������ �ȵǴϱ� return
		if (*m_OtherStart == _OtherGroup)
		{
			return;
		}
	}

	Tassert(nullptr == _OtherGroup);

	if (nullptr == _OtherGroup)
	{
		return;
	}

	m_OtherColGroup.push_back(_OtherGroup);
}


void CollisionManager::CollisionCroup::Insert_Collision(ObjectCollision* _ObjCol)
{
	m_ObjColList.push_back(_ObjCol);
}


void CollisionManager::CollisionCroup::Collision_Check(CollisionCroup* _OtherGroup)
{
	// �� = ��(_OtherGroup) �� ��� (���� �׷��� ���) 
	if (this == _OtherGroup)
	{
		// �ٸ� �׷��� ��� 
		m_ThisStartIter = m_ObjColList.begin();		// �� �׷�
		m_ThisEndIter = m_ObjColList.end();

		for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
		{
			if (false == (*m_ThisStartIter)->IsObjUpdate())
			{
				continue;
			}

			m_OtherStartIter = m_ThisStartIter;  // �ٸ��׷�
			m_OtherEndIter = m_ThisEndIter;

			++m_OtherStartIter;

			for (; m_OtherStartIter != m_OtherEndIter; ++m_OtherStartIter)
			{
				if (false == (*m_OtherStartIter)->IsObjUpdate())
				{
					continue;
				}

				(*m_ThisStartIter)->Collision_Check(*m_OtherStartIter);
			}

		}
	}
	else
	{
		// �ٸ� �׷��� ��� 
		m_ThisStartIter = m_ObjColList.begin();		// �� �׷�
		m_ThisEndIter = m_ObjColList.end();

		for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
		{
			if (false == (*m_ThisStartIter)->IsObjUpdate())
			{
				continue;
			}

			m_OtherStartIter = _OtherGroup->m_ObjColList.begin();   // �ٸ��׷�
			m_OtherEndIter = _OtherGroup->m_ObjColList.end();

			for (; m_OtherStartIter != m_OtherEndIter; ++m_OtherStartIter)
			{
				if (false == (*m_OtherStartIter)->IsObjUpdate())
				{
					continue;
				}

				(*m_ThisStartIter)->Collision_Check(*m_OtherStartIter);
			}

		}
	}
}

void CollisionManager::CollisionCroup::Collision_Update()
{
	m_OtherStart = m_OtherColGroup.begin();
	m_OtherEnd = m_OtherColGroup.end();

	for ( ; m_OtherStart != m_OtherEnd; ++m_OtherStart)
	{
		CollisionCroup* OtherColList = *m_OtherStart;
		Collision_Check(OtherColList);
	}
}

void CollisionManager::CollisionCroup::Collision_Setting()
{
	m_ThisStartIter = m_ObjColList.begin();
	m_ThisEndIter = m_ObjColList.end();

	for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
	{
		(*m_ThisStartIter)->ParentPosSetting();
	}
}

//����
void CollisionManager::CollisionCroup::Release()
{
	m_ThisStartIter = m_ObjColList.begin();
	m_ThisEndIter = m_ObjColList.end();

	for ( ; m_ThisStartIter != m_ThisEndIter; )
	{
		if (true == (*m_ThisStartIter)->IsObjDeath())
		{
			m_ThisStartIter = m_ObjColList.erase(m_ThisStartIter);
		}
		else
		{
			++m_ThisStartIter;
		}
	}
}

// �����
void CollisionManager::CollisionCroup::DebugRender()
{
	m_ThisStartIter = m_ObjColList.begin();
	m_ThisEndIter = m_ObjColList.end();

	for ( ; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
	{
		(*m_ThisStartIter)->DebugRender();
	}
}



////// CollisionManager Ŭ����

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End = m_ColGroupMap.end();

	for ( ; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
		}
	}

	m_ColGroupMap.clear();
}

CollisionManager::CollisionCroup* CollisionManager::FindColGroup(const wchar_t* _GroupName)
{
	m_FindGroupIter = m_ColGroupMap.find(_GroupName);

	// �ش� �׷��� ���ٸ� �߰�
	if (m_FindGroupIter == m_ColGroupMap.end())
	{
		CollisionCroup* pColGroup = new CollisionCroup;
		pColGroup->Name = _GroupName;
		m_ColGroupMap.insert(std::map<std::wstring, CollisionCroup*>::value_type(_GroupName, pColGroup));
		return pColGroup;
	}

	return m_FindGroupIter->second;
}

void CollisionManager::Insert_Collision(const wchar_t* _GroupName, ObjectCollision* _ObjCol)
{
	CollisionCroup* pColGroup = FindColGroup(_GroupName);		// �׷�ã��

	// �ش� �׷��� ���ٸ� ( �׷��� �������� �ʾҴٸ� )
	Tassert(nullptr == pColGroup);
	if (nullptr == pColGroup)
	{
		return;
	}

	pColGroup->Insert_Collision(_ObjCol);

}

void CollisionManager::Link(const wchar_t* _Left, const wchar_t* _Right)
{
	CollisionCroup* pLeft = FindColGroup(_Left);
	CollisionCroup* pRight = FindColGroup(_Right);

	Tassert(nullptr == pLeft);
	Tassert(nullptr == pRight);

	if (nullptr == pLeft || nullptr == pRight)
	{
		return;
	}

	// �ߺ��ؼ� ���ʿ䰡 ����  pRight->Link(pLeft)
	pLeft->Link(pRight);
}


// ��� �׷��� Collision üũ�� ���⼭ �ϹǷ� ��� ��������(Scene)���� �̰� ����������Ѵ�.
void CollisionManager::Collision_Update()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start_Iter = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End_Iter = m_ColGroupMap.end();

	for ( ; Start_Iter != End_Iter; ++Start_Iter)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->Collision_Setting();
			Start_Iter->second->Collision_Update();
		}
	}
}

void CollisionManager::Release()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start_Iter = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End_Iter = m_ColGroupMap.end();

	for (; Start_Iter != End_Iter; ++Start_Iter)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->Release();
		}
	}
}

// ����� 
void CollisionManager::DebugRender()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start_Iter = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End_Iter = m_ColGroupMap.end();

	for ( ; Start_Iter != End_Iter; ++Start_Iter)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->DebugRender();
		}
	}
}
