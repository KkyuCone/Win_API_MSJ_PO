#pragma once
#include "GameObjectImage.h"

class ResourceManager;
class GameObjectMultiSprite;
class GameObjectSprite
{
public:
	friend ResourceManager;
	friend GameObjectMultiSprite;

private:
	GameObjectImage* m_ObjImage;
	F_Rectangle m_Rectangle;

public:
	inline bool IsAlpha()
	{
		return m_ObjImage->Alpha_Value();
	}

	inline HDC ObjectImageDC()
	{
		return m_ObjImage->ObjectImageDC();
	}

	inline F_Position Pos()
	{
		return m_Rectangle.Position;
	}

	inline UINT TransColor()
	{
		return m_ObjImage->TransColor();
	}

	inline F_Position Size()
	{
		return m_Rectangle.Size;
	}

public:
	void PosX()
	{

	}

	void PosY()
	{

	}

public:
	GameObjectSprite(GameObjectImage* _ObjImage, F_Position _FPos, F_Size _FSize);
	~GameObjectSprite();
};

