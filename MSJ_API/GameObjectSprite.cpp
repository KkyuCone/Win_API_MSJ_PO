#include "stdafx.h"
#include "GameObjectSprite.h"


GameObjectSprite::GameObjectSprite(GameObjectImage* _ObjImage, F_Position _FPos, F_Size _FSize)
	: m_ObjImage(_ObjImage), m_Rectangle(_FPos, _FSize)
{
}


GameObjectSprite::~GameObjectSprite()
{
}
