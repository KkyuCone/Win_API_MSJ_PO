#pragma once
#include "ActorObjBase.h"

class ObjectCollision;
class AnimationRenderer;
class PixelColGround : public ActorObjBase
{
private:
	AnimationRenderer* m_ExitAniRenderer;
	ObjectCollision* m_ExitButtonCol;


public:
	void Start_Update() override;

public:
	void GameExit(ObjectCollision* _This, ObjectCollision* _Other);

public:
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) override;


public:
	PixelColGround();
	~PixelColGround();
};

