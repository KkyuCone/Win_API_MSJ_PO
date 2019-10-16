#pragma once
#include <fmod.hpp>

class SoundSource;
class ResourceManager;
class SoundControl
{
private:
	friend ResourceManager;

public:
	SoundSource* m_pSoundSource;
	FMOD::Channel* m_pSoundChannel;
	float m_Ptich;

public:
	float Sound_GetPitch();
	void Sound_SetPitch(float _Value);

	bool Sound_IsPlay();
	//void Sound_Stop();

	void Sound_NewPlay(const wchar_t* _SoundFile);
	void SoundControl::Sound_NewPlayItem(const wchar_t* _SoundFile);

	void Sound_Stop();

public:
	SoundControl();

private:
	~SoundControl();
};

