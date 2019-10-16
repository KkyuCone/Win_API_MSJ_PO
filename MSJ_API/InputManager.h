#pragma once

#include <Windows.h>

#include <map>
#include <vector>

#include "TimeManager.h"
#include "Util_Core.h"
#include "TAssert.h"
#include "Render_Vector.h"

// 입력
class InputManager
{
public:
	static InputManager& Instance()
	{
		static InputManager instance = InputManager();
		return instance;
	}

public:
	class Input_KeyData
	{
	private:
		friend InputManager;
	private:
		std::vector<int> m_InputKey;  // 입력받은 키 저장
		bool m_ButtonUp;
		bool m_ButtonUpStay;
		bool m_ButtonDown;
		bool m_ButttonDownStay;

		float PushTime;

	private:
		template<typename... Variable_Argument>
		void Push_Key(const int _val, Variable_Argument... _arg)
		{
			m_InputKey.push_back(_val);
			Push_Key(_arg...);
		}
		// 재귀를 빠져나오기 위해 사용
		void Push_Key()
		{

		}

	public:
		// 키 체크
		void Input_Update();
		bool Key_Check();

	public:
		Input_KeyData(size_t _number) : m_ButtonUpStay(true), m_ButtonUp(false), m_ButtonDown(false), m_ButttonDownStay(false)
		{
			m_InputKey.reserve(_number);
		}
	};

public:
	friend Util_Core;

private:
	std::map<std::wstring, Input_KeyData*>::iterator Start_Iter;
	std::map<std::wstring, Input_KeyData*>::iterator End_Iter;
	std::map<std::wstring, Input_KeyData*> m_InputMapKeyData;

	POINT MousePosition;

public:
	I_Position MousePos()
	{
		return{ MousePosition.x, MousePosition.y };
	}

	F_Position MousePos_F()
	{
		return{ MousePosition.x, MousePosition.y };
	}

private:
	Input_KeyData* Find_Key(const wchar_t* _key)
	{
		std::map<std::wstring, Input_KeyData*>::iterator KeyFind_Iter = m_InputMapKeyData.find(_key);
		
		if (KeyFind_Iter == m_InputMapKeyData.end())
		{
			return nullptr;
		}

		return KeyFind_Iter->second;
	}

public:
	template<typename... Variable_Argument>
	bool Create_Key(const wchar_t* _key, Variable_Argument... _arg)
	{
		Input_KeyData* NewKey = Find_Key(_key); // 키찾기

		if (NewKey != nullptr)
		{
			// 이미 키가 존재한다면 터진다.
			Tassert(true);
			return false;
		}

		// 키가 없다면 키 추가
		NewKey = new Input_KeyData(sizeof...(_arg));	// 몇개의 조합키인지 알기위해
		NewKey->Push_Key(_arg...);	// 키넣기

		m_InputMapKeyData.insert(std::map<std::wstring, Input_KeyData*>::value_type(_key, NewKey));

		return true;

	}

private:
	// 아래의 Update함수는 절대로 다른곳에서 실행하면 안된다.(터짐)
	void InputManager_Update();

public:
	bool Up(const wchar_t* _name);
	bool Down(const wchar_t* _name);
	bool UpStay(const wchar_t* _name);
	bool DownStay(const wchar_t* _name);

	float PushTimer(const wchar_t* Name);
	bool PushTimerReset(const wchar_t* _Name, float _Time);

public:
	InputManager();
	~InputManager();
};

