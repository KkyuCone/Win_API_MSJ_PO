#include "stdafx.h"
#include "SoundSource.h"
#include "ResourceManager.h"
#include <atlstr.h>			// atlstr은 문자열 편의 함수들 제공 ( 윈도우에서 지원하는 라이브러리중 하나 ), stl과 관련된 편의함수임

////////////////////////////////////////
SoundSource::SoundSource() : m_SoundLength(0)
{
}


SoundSource::~SoundSource()
{
	m_pSoundSource->release();
}

/////////////////////////////////////////

bool SoundSource::Sound_Load(const wchar_t* _Path)
{
	// 와이드바이트 -> 멀티바이트
	// WideCharToMultiByte()  1번

	// CW2A 함수객체사용 2번
	//std::string MultiBytePath = CW2A(_Path)
	// UTF8 형식의 문자열만을 PATH로 받아준다. 
	std::string MultiBytePath = CW2A(_Path, CP_UTF8).m_psz;


	if (FMOD_OK != ResourceManager::Instance().m_pSoundSystem->createSound(MultiBytePath.c_str(), DMDFO_DEFAULT, nullptr, &m_pSoundSource))
	{
		Tassert(true);
		return false;
	}

	Tassert(nullptr == m_pSoundSource);

	if (nullptr == m_pSoundSource)
	{
		return false;
	}

	m_pSoundSource->getLength(&m_SoundLength, FMOD_TIMEUNIT_MS);

	return true;
}

bool SoundSource::SoundBGM_Load(const wchar_t* _Path)
{
	// 와이드바이트 -> 멀티바이트
	// WideCharToMultiByte()  1번

	// CW2A 함수객체사용 2번
	//std::string MultiBytePath = CW2A(_Path)
	// UTF8 형식의 문자열만을 PATH로 받아준다. 
	std::string MultiBytePath = CW2A(_Path, CP_UTF8).m_psz;


	if (FMOD_OK != ResourceManager::Instance().m_pSoundSystem->createStream(MultiBytePath.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_pSoundSource))
	{
		Tassert(true);
		return false;
	}

	Tassert(nullptr == m_pSoundSource);

	if (nullptr == m_pSoundSource)
	{
		return false;
	}

	m_pSoundSource->getLength(&m_SoundLength, FMOD_TIMEUNIT_MS);

	return true;
}