#pragma once
#include "ObjUpdateBase.h"
#include <string>

class ObjNameBase : public ObjUpdateBase
{
private:
	std::wstring m_ObjName;

public:
	inline void Name(const wchar_t* _Name)
	{
		m_ObjName = _Name;
	}

	inline const wchar_t* Name() const
	{
		return m_ObjName.c_str();
	}

	inline bool NameEqual(const wchar_t* _Name) const
	{
		return (m_ObjName == _Name);
	}
public:
	ObjNameBase();
	~ObjNameBase();
};

