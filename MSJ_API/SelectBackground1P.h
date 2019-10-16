#pragma once
#include "ActorObjBase.h"

class AnimationRenderer;
class SelectBackground1P : public ActorObjBase
{
private:
	AnimationRenderer* m_FadeInRenderer;
	bool m_FadeIn;
public:
	void Start_Update() override;
	void Update() override;
public:
	SelectBackground1P();
	~SelectBackground1P();
};

