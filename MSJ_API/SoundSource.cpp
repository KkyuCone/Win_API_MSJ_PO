#include "stdafx.h"
#include "SoundSource.h"
#include "ResourceManager.h"
#include <atlstr.h>			// atlstr�� ���ڿ� ���� �Լ��� ���� ( �����쿡�� �����ϴ� ���̺귯���� �ϳ� ), stl�� ���õ� �����Լ���

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
	// ���̵����Ʈ -> ��Ƽ����Ʈ
	// WideCharToMultiByte()  1��

	// CW2A �Լ���ü��� 2��
	//std::string MultiBytePath = CW2A(_Path)
	// UTF8 ������ ���ڿ����� PATH�� �޾��ش�. 
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
	// ���̵����Ʈ -> ��Ƽ����Ʈ
	// WideCharToMultiByte()  1��

	// CW2A �Լ���ü��� 2��
	//std::string MultiBytePath = CW2A(_Path)
	// UTF8 ������ ���ڿ����� PATH�� �޾��ش�. 
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