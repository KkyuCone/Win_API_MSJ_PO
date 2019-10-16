#pragma once
#include "MainSceneState.h"

class Player;
class SoundControl;
class Bubble;
class PlayStage :  public MainSceneState
{
public:
	friend class Util_Core;

private:
	SoundControl* m_SoundControl;

private:
	void Start_Update() override;
	void End_Debug_Update() override;

	void Loading() override;

public:
	std::map<__int64, Bubble*> m_BubbleMap;

public:
	void LoadMap();

public:
	PlayStage();
	~PlayStage();

public:
	void BGM_ON();
};

