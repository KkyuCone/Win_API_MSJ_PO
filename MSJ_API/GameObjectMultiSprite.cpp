#include "stdafx.h"
#include "GameObjectMultiSprite.h"


GameObjectMultiSprite::GameObjectMultiSprite(size_t _Count)
{
	m_ObjSprite.reserve(_Count);
}

GameObjectMultiSprite::~GameObjectMultiSprite()
{
	for (size_t i = 0; i < m_ObjSprite.size(); i++)
	{
		delete m_ObjSprite[i];
		m_ObjSprite[i] = nullptr;
	}

	m_ObjSprite.clear();
}

/////////////////////////////////////////////////////////////////

void GameObjectMultiSprite::Sprite_Insert(GameObjectSprite * _pSprite)
{
	m_ObjSprite.push_back(_pSprite);
}


// Ãß°¡


