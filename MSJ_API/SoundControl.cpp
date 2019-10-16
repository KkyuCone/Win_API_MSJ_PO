#include "stdafx.h"
#include "SoundControl.h"
#include "ResourceManager.h"
#include "SoundSource.h"


SoundControl::SoundControl() : m_pSoundChannel(nullptr)
{
}


SoundControl::~SoundControl()
{
}

// 속도반환
float SoundControl::Sound_GetPitch()
{
	m_pSoundChannel->getPitch(&m_Ptich);
	return m_Ptich;
}

// 속도지정
void SoundControl::Sound_SetPitch(float _Value)
{
	m_Ptich = _Value;
	m_pSoundChannel->setPitch(m_Ptich);
	return;
}

bool SoundControl::Sound_IsPlay()
{
	bool bPlaying;
	m_pSoundChannel->isPlaying(&bPlaying);
	return bPlaying;
}

void SoundControl::Sound_NewPlay(const wchar_t* _SoundFile)
{
	if (nullptr != m_pSoundChannel)
	{
		m_pSoundChannel->stop();
	}

	SoundSource* pNewSound = ResourceManager::Instance().Sound_Find(_SoundFile);

	Tassert(nullptr == pNewSound);

	if (nullptr == pNewSound)
	{
		return;
	}

	ResourceManager::Instance().m_pSoundSystem->playSound(pNewSound->Get_Sound(), nullptr, false, &m_pSoundChannel);
	Sound_GetPitch();
}

void SoundControl::Sound_NewPlayItem(const wchar_t* _SoundFile)
{
	SoundSource* pNewSound = ResourceManager::Instance().Sound_Find(_SoundFile);

	Tassert(nullptr == pNewSound);

	if (nullptr == pNewSound)
	{
		return;
	}

	ResourceManager::Instance().m_pSoundSystem->playSound(pNewSound->Get_Sound(), nullptr, false, &m_pSoundChannel);
	Sound_GetPitch();
}

void SoundControl::Sound_Stop()
{
	if (nullptr != m_pSoundChannel)
	{
		m_pSoundChannel->stop();
	}
}

