#pragma once
#include "ActorObjBase.h"

class AnimationRenderer;
class PlayBackGround : public ActorObjBase
{
private:
	AnimationRenderer* m_FadeInRenderer;
	bool m_FadeIn;

public:
	void Start_Update() override;
	void Update() override;
	void DebugRender() override;

public:
	PlayBackGround();
	~PlayBackGround();
};

