#include "stdafx.h"
#include "InputManager.h"


/////////////////////////////////////////////// Input_KeyData

bool InputManager::Input_KeyData::Key_Check()
{
	for (size_t i = 0; i < m_InputKey.size(); i++)
	{
		// 해당 키가 눌리지 않았다면
		if (0 == GetAsyncKeyState(m_InputKey[i]))
		{
			return false;
		}
	}
	return true;
}

void InputManager::Input_KeyData::Input_Update()
{
	bool KeyCheck_Vlaue = Key_Check();	// 키가 눌렸는지 체크

	if (true == KeyCheck_Vlaue)
	{
		// 키가 눌렸을때
		if (true == m_ButtonUpStay)
		{
			// 눌린 그 순간
			m_ButtonUp = false;
			m_ButtonUpStay = false;
			m_ButtonDown = true;		// 키가 눌린 한순간
			m_ButttonDownStay = true;
		}
		else if (false == m_ButtonUpStay)
		{
			// 눌린 순간이 지났을때 ( 키를 누르고 뗐을때 )
			m_ButtonUp = false;
			m_ButtonUpStay = false;
			m_ButtonDown = false;
			m_ButttonDownStay = true;
		}
	}
	else if (false == KeyCheck_Vlaue)
	{
		// 키가 안눌렸을때
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
	Input_KeyData* mp_KeyData = Find_Key(_name);	// 키 찾기
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButtonUp;
}

bool InputManager::Down(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// 키 찾기
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButtonDown;
}

bool InputManager::UpStay(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// 키 찾기
	Tassert(nullptr == mp_KeyData);

	if (nullptr == mp_KeyData)
	{
		return false;
	}
	return mp_KeyData->m_ButtonUpStay;
}

bool InputManager::DownStay(const wchar_t * _name)
{
	Input_KeyData* mp_KeyData = Find_Key(_name);	// 키 찾기
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