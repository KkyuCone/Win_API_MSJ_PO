#pragma once
#include <fmod.hpp>

class SoundSource
{
private:
	FMOD::Sound* m_pSoundSource;
	UINT m_SoundLength;

public:
	FMOD::Sound* Get_Sound()
	{
		return m_pSoundSource;
	}

public:
	bool Sound_Load(const wchar_t* _Path);
	bool SoundSource::SoundBGM_Load(const wchar_t* _Path);

public:
	SoundSource();
	~SoundSource();
};

