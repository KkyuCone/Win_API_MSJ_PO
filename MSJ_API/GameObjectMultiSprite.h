#pragma once
#include "GameObjectSprite.h"
#include <vector>

class ResourceManager;
class GameObjectMultiSprite
{
private:
	friend ResourceManager;

private:
	std::vector<GameObjectSprite*> m_ObjSprite;

private:
	void Sprite_Insert(GameObjectSprite* _pSprite);

public:
	inline GameObjectSprite* GetSprite(size_t _idx)
	{
		return m_ObjSprite[_idx];
	}

	size_t SpriteCount()
	{
		return m_ObjSprite.size();
	}

public:
	GameObjectMultiSprite(size_t _Count);
	~GameObjectMultiSprite();
};

