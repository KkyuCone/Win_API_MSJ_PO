#include "stdafx.h"
#include "InputManager.h"


/////////////////////////////////////////////// Input_KeyData

bool InputManager::Input_KeyData::Key_Check()
{
	for (size_t i = 0; i < m_InputKey.size(); i++)
	{
		// �ش� Ű�� ������ �ʾҴٸ�
		if (0 == GetAsyncKeyState(m_InputKey[i]))
		{
			return false;
		}
	}
	return true;
}

void InputManager::Input_KeyData::Input_Update()
{
	bool KeyCheck_Vlaue = Key_Check();	// Ű�� ���ȴ��� üũ

	if (true == KeyCheck_Vlaue)
	{
		// Ű�� ��������
		if (true == m_ButtonUpStay)
		{
			// ���� �� ����
			m_ButtonUp = false;
			m_ButtonUpStay = false;
			m_ButtonDown = true;		// Ű�� ���� �Ѽ���
			m_ButttonDownStay = true;
		}
		else if (false == m_ButtonUpStay)
		{
			// ���� ������ �������� ( Ű�� ������ ������ )
			m_ButtonUp = false;
			m_ButtonUpStay = false;
			m_ButtonDown = false;
			m_ButttonDownStay = true;
		}
	}
	else if (false == KeyCheck_Vlaue)
	{
		// Ű�� �ȴ�������
		if (true == m_ButttonDownStay)
		{
			m_ButtonUp = true;
			m_ButtonUpStay = true;
			m_ButtonDown = false;
			m_ButttonDownStay = false;
		}
		else if (false == m_ButttonDownStay)
		{
			m_ButtonUp = false;
			m_ButtonUpStay = true;
			m_ButtonDown = false;
			m_ButttonDownStay = false;
		}
	}
}

///////////////////////////////////////////////


/////////////////////////////////////////////// InputManager

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
	Start_Iter = m_InputMapKeyData.begin();
	End_Iter = m_InputMapKeyData.end();

	for (; Start_Iter != End_Iter; Start_Iter++)
	{
		if (nullptr != Start_Iter->second)
		{
			delete Start_Iter->second;
			Start_Iter->second = nullptr;
		}
	}

	m_InputMapKeyData.clear();
}

void InputManager::InputManager_Update()
{
	GetCursorPos(&MousePosition);
	ScreenToClient(Util_Core::Instance().WINDOW_HWND(), &MousePosition);

	Start_Iter = m_InputMapKeyData.begin();
	End_Iter = m_InputMapKeyData.end();

	for (; Start_Iter != End_Iter; Start_Iter++)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->Input_Update();
		}
	}
}

bool InputManager::Up(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// Ű ã��
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButtonUp;
}

bool InputManager::Down(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// Ű ã��
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButtonDown;
}

bool InputManager::UpStay(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// Ű ã��
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButtonUpStay;
}

bool InputManager::DownStay(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// Ű ã��
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButttonDownStay;
}

float InputManager::PushTimer(const wchar_t * Name)
{
	return 0.0f;
}

bool InputManager::PushTimerReset(const wchar_t * _Name, float _Time)
{
	return false;
}


///////////////////////////////////////////////