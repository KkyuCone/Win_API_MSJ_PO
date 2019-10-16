#pragma once
#include "ObjectRenderer.h"

class GameObjectSprite;
class SingleRenderer : public ObjectRenderer
{
private:
	GameObjectSprite* m_pSpriteImage;

public:
	void SettingSprite(const wchar_t* _pImageName);
	void SettingSprite(const wchar_t* _pImageName, size_t _Count);

private:
	void Render() override;

public:
	SingleRenderer();
	~SingleRenderer();
};

