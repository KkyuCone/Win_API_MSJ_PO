#pragma once

#include <map>
#include <string>
#include <list>
#include <set>
#include <fmod.hpp>

// dll을 추가로 로드할 경우 자기파일이 있는곳에 두면 자동으로 로드, 다른 폴더에 있다면 경로를 알려줘야한다.
#pragma comment(lib, "fmod_vc")


// 리소스들은 경로가 존재한다.

class SoundSource;
class SoundControl;
class GameObjectImage;
class GameObjectSprite;
class GameObjectMultiSprite;
class ResourceManager
{
public:
	static ResourceManager& Instance()
	{
		static ResourceManager instance = ResourceManager();
		return instance;
	}

public:
	ResourceManager();
	~ResourceManager();

/////////////////////////////////// Path
private:
	//       //texture     c:\\game\bin\aaa.bmp
	std::map<std::wstring, std::wstring> m_ImagePath;
	std::wstring m_RootPath;		// 게임이 실행되고 있는 폴더의 경로

public:
	void ResMgr_Init();
	std::wstring FindPath(const wchar_t* _Key);

	bool RootPath_Create(const wchar_t* _Key);
	bool RootPath_Create(const wchar_t* _Key, const wchar_t* _Folder);

public:
	std::wstring RootPath()
	{
		return m_RootPath;
	}

	const wchar_t* RootPath_pAddress()
	{
		return m_RootPath.c_str();
	}

///////////////////////////////////////////////// BackBuffer
private:
	GameObjectImage* m_BackBuffer;

public:
	HDC BackBufferDC();


///////////////////////////////////////////////// Image


private:
	std::map<std::wstring, GameObjectImage*> m_GameObjImage;

public:
	GameObjectImage* LoadToPathImage(const wchar_t* _FolderKey, const wchar_t* _ImageName, UINT _TransColor = RGB(255, 0, 255));
	GameObjectImage* Find_Image(const wchar_t* _ImageName);


///////////////////////////////////////////////// Sprite


private:
	std::map<std::wstring, GameObjectSprite*> m_GameObjSprite;

public:
	GameObjectSprite* Sprite_Create(const wchar_t* _ImageName);
	GameObjectSprite* Sprite_Create(const wchar_t* _ImageName, F_Position _FPos, F_Size _FSize);
	GameObjectSprite* Sprite_Create(const wchar_t* _SpriteName, const wchar_t* _ImageName, F_Position _FPos, F_Size _FSize);

	GameObjectSprite* Find_Sprite(const wchar_t* _SpriteName);



///////////////////////////////////////////////// MultiSprite
private:
	std::map<std::wstring, GameObjectMultiSprite*> m_ObjMultiSprite;

public:
	GameObjectMultiSprite* MultiSprite_Create(const wchar_t* _ImageName, I_Size _Size);
	GameObjectMultiSprite* MultiSprite_Create(const wchar_t* _SpriteName, const wchar_t* _ImageName, I_Size _Size);

	GameObjectMultiSprite* Find_MultiSprite(const wchar_t* _SpriteName);
	GameObjectSprite* Find_Sprite(const wchar_t* _SpriteName, size_t _idx);



///////////////////////////////////////////////// Sound
private:
	FMOD::System* m_pSoundSystem;
	std::map<std::wstring, SoundSource*> m_SoundSource;

	std::set<SoundControl*> m_SoundControl;

public:
	SoundControl* SoundControl_Insert();
	bool SoundControl_Erase(SoundControl* _SoundControl);

public:
	friend SoundSource;
	friend SoundControl;

public:
	SoundSource* Sound_Load(const wchar_t* _Folder, const wchar_t* _Name);
	SoundSource* Sound_Find(const wchar_t* _Name);

	void Sound_Paly(const wchar_t* _Name);


	SoundSource* SoundBGM_Load(const wchar_t* _Folder, const wchar_t* _Name);

};

