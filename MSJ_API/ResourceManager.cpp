#include "stdafx.h"
#include "ResourceManager.h"
#include "GameObjectMultiSprite.h"
#include "SoundSource.h"
#include "SoundControl.h"

ResourceManager::ResourceManager() : m_pSoundSystem(nullptr)
{
}


ResourceManager::~ResourceManager()
{
	std::map<std::wstring, GameObjectImage*>::iterator Start_Iter = m_GameObjImage.begin();
	std::map<std::wstring, GameObjectImage*>::iterator End_Iter = m_GameObjImage.end();

	for (; Start_Iter != End_Iter; Start_Iter++)
	{
		if (nullptr != Start_Iter->second)
		{
			delete Start_Iter->second;
		}
	}

	std::map<std::wstring, GameObjectSprite*>::iterator StartSprite_Iter = m_GameObjSprite.begin();
	std::map<std::wstring, GameObjectSprite*>::iterator EndSprite_Iter = m_GameObjSprite.end();

	for (; StartSprite_Iter != EndSprite_Iter; StartSprite_Iter++)
	{
		if (nullptr != StartSprite_Iter->second)
		{
			delete StartSprite_Iter->second;
		}
	}

	std::map<std::wstring, GameObjectMultiSprite*>::iterator StartMulti_Iter = m_ObjMultiSprite.begin();
	std::map<std::wstring, GameObjectMultiSprite*>::iterator EndSMulti_Iter = m_ObjMultiSprite.end();

	for (; StartMulti_Iter != EndSMulti_Iter; StartMulti_Iter++)
	{
		if (nullptr != StartMulti_Iter->second)
		{
			delete StartMulti_Iter->second;
		}
	}

	if (nullptr != m_BackBuffer)
	{
		delete m_BackBuffer;
	}

	std::map<std::wstring, SoundSource*>::iterator SoundSource_StartIter = m_SoundSource.begin();
	std::map<std::wstring, SoundSource*>::iterator SoundSource_EndIter = m_SoundSource.end();

	for (; SoundSource_StartIter != SoundSource_EndIter; ++SoundSource_StartIter)
	{
		if (nullptr != SoundSource_StartIter->second)
		{
			delete SoundSource_StartIter->second;
		}
	}

	std::set<SoundControl*>::iterator SoundControl_StartIter = m_SoundControl.begin();
	std::set<SoundControl*>::iterator SoundControl_EndIter = m_SoundControl.end();

	for (; SoundControl_StartIter != SoundControl_EndIter; ++SoundControl_StartIter)
	{
		delete
			*SoundControl_StartIter;
	}

	if (nullptr != m_pSoundSystem)
	{
		m_pSoundSystem->release();
	}
}

////////////////////////////////////////////// Path
void ResourceManager::ResMgr_Init()
{
	wchar_t ArrString[256] = {};
	GetCurrentDirectoryW(sizeof(wchar_t) * 256, ArrString);
	m_RootPath = ArrString;

	// 어떤 문자열의 특정 문자를 뒤에서 부터 찾아서
	// 그게 나오면 그 위치를 리턴한다.
	// 
	// 012345678910
	// \\SSSD\\SSSS\\DBD
	size_t CutCount = m_RootPath.find_last_of(L'\\', m_RootPath.size());
	m_RootPath = m_RootPath.replace(CutCount, m_RootPath.size(), L"\\ResourceBMP\\");


	// 화면 크기 설정
	m_BackBuffer = new GameObjectImage();

	if (nullptr != m_BackBuffer)
	{
		m_BackBuffer->Create_EmptyImage({ (float)Util_Core::Instance().WINDOWN_SIZE().X, (float)Util_Core::Instance().WINDOWN_SIZE().Y });
	}

	// 시스템 얻어서 주기
	FMOD::System_Create(&m_pSoundSystem);
	Tassert(nullptr == m_pSoundSystem);

	if (nullptr == m_pSoundSystem)
	{
		return;
	}

	// 32 -> 최대 1000개를 재생할 수 있음
	FMOD_RESULT SoundCount = m_pSoundSystem->init(32, FMOD_DEFAULT, nullptr);

	Tassert(FMOD_OK != SoundCount);
}

std::wstring ResourceManager::FindPath(const wchar_t * _Key)
{
	std::map<std::wstring, std::wstring>::iterator Find_Iter = m_ImagePath.find(_Key);

	if (Find_Iter != m_ImagePath.end())
	{
		return Find_Iter->second;
	}

	return L"";
}

bool ResourceManager::RootPath_Create(const wchar_t * _Key)
{
	return RootPath_Create(_Key, _Key);
}

bool ResourceManager::RootPath_Create(const wchar_t * _Key, const wchar_t * _Folder)
{
	std::map<std::wstring, std::wstring>::iterator Find_Iter = m_ImagePath.find(_Key);

	// 이미 등록되어있다면
	if (Find_Iter != m_ImagePath.end())
	{
		Tassert(true);
		return false;
	}

	m_ImagePath.insert(std::map<std::wstring, std::wstring>::value_type(_Key, m_RootPath + _Folder + L"\\"));
	
	return true;
}

//////////////////////////////////////////////////// BackBuffer

HDC ResourceManager::BackBufferDC()
{
	return m_BackBuffer->ObjectImageDC();
}


////////////////////////////////////////////// Iamge


GameObjectImage * ResourceManager::LoadToPathImage(const wchar_t * _FolderKey, const wchar_t * _ImageName, UINT _TransColor)
{
	// 이미지 이름이 겹치면 안됨
	std::map<std::wstring, GameObjectImage*>::iterator Iter = m_GameObjImage.find(_ImageName);

	// 이미 있다면
	if (Iter != m_GameObjImage.end())
	{
		return Iter->second;
	}

	std::wstring ImagePath = FindPath(_FolderKey);
	ImagePath += _ImageName;

	GameObjectImage* NewImage = new GameObjectImage();
	NewImage->TransColor(_TransColor);

	if (false == NewImage->Resource_Load(ImagePath.c_str()))
	{
		delete NewImage;
		Tassert(true);
		return nullptr;
	}

	m_GameObjImage.insert(std::map<std::wstring, GameObjectImage*>::value_type(_ImageName, NewImage));
	return NewImage;
}

GameObjectImage * ResourceManager::Find_Image(const wchar_t * _ImageName)
{
	std::map<std::wstring, GameObjectImage*>::iterator Find_Iter = m_GameObjImage.find(_ImageName);

	if (Find_Iter == m_GameObjImage.end())
	{
		return nullptr;
	}

	return Find_Iter->second;
}


///////////////////////////////////////////////// Sprite

GameObjectSprite* ResourceManager::Sprite_Create(const wchar_t* _ImageName)
{
	GameObjectImage* p_ObjImage = Find_Image(_ImageName);
	Tassert(nullptr == p_ObjImage);

	if (nullptr == p_ObjImage)
	{
		return nullptr;
	}

	return Sprite_Create(_ImageName, _ImageName, F_Position::ZERO, F_Position(p_ObjImage->Width(), p_ObjImage->Height()));
}

GameObjectSprite * ResourceManager::Sprite_Create(const wchar_t * _ImageName, F_Position _FPos, F_Size _FSize)
{
	return Sprite_Create(_ImageName, _ImageName, _FPos, _FSize);
}

GameObjectSprite * ResourceManager::Sprite_Create(const wchar_t * _SpriteName, const wchar_t * _ImageName, F_Position _FPos, F_Size _FSize)
{
	// 이미지 이름이 겹치면 안됨
	GameObjectSprite* pObjSprite = Find_Sprite(_SpriteName);

	// 이미 해당 스프라이트가 있을 경우
	if (nullptr != pObjSprite)
	{
		return pObjSprite;
	}

	GameObjectImage* pFindImage = Find_Image(_ImageName);

	Tassert(nullptr == pFindImage);

	if (nullptr == pFindImage)
	{
		return nullptr;
	}

	GameObjectSprite* pNewSprite = new GameObjectSprite(pFindImage, _FPos, _FSize);
	m_GameObjSprite.insert(std::map<std::wstring, GameObjectSprite*>::value_type(_SpriteName, pNewSprite));

	return pNewSprite;
}

// 스프라이트 찾기 
GameObjectSprite * ResourceManager::Find_Sprite(const wchar_t * _SpriteName)
{
	std::map<std::wstring, GameObjectSprite*>::iterator Find_Iter = m_GameObjSprite.find(_SpriteName);

	if (Find_Iter == m_GameObjSprite.end())
	{
		return nullptr;
	}

	return Find_Iter->second;
}


///////////////////////////////////////////////// MultiSprite

GameObjectMultiSprite * ResourceManager::MultiSprite_Create(const wchar_t * _ImageName, I_Size _Size)
{
	return MultiSprite_Create(_ImageName, _ImageName, _Size);
}

GameObjectMultiSprite * ResourceManager::MultiSprite_Create(const wchar_t * _SpriteName, const wchar_t * _ImageName, I_Size _Size)
{
	Tassert(0 == _Size.X);
	Tassert(0 == _Size.Y);

	GameObjectMultiSprite* pMultiSprite = Find_MultiSprite(_SpriteName);

	if (nullptr != pMultiSprite)
	{
		return pMultiSprite;
	}

	GameObjectImage* pObjImage = Find_Image(_ImageName);
	Tassert(nullptr == pObjImage);
	if (nullptr == pObjImage)
	{
		return nullptr;
	}

	F_Size SpriteSize = F_Size();

	SpriteSize.X = pObjImage->Width() / (float)_Size.X;
	SpriteSize.Y = pObjImage->Height() / (float)_Size.Y;

	GameObjectMultiSprite* pNewObjMultiSprite = new GameObjectMultiSprite(_Size.X * _Size.Y);

	F_Position SpritePos = F_Position();

	for (int y = 0; y < _Size.Y; y++)
	{
		for (int x = 0; x < _Size.X; x++)
		{
			GameObjectSprite* pNewSprite = new GameObjectSprite(pObjImage, SpritePos, SpriteSize);
			pNewObjMultiSprite->Sprite_Insert(pNewSprite);
			SpritePos.X += SpriteSize.X;
		}

		SpritePos = { 0, SpritePos.Y + SpriteSize.Y };
	}

	m_ObjMultiSprite.insert(std::map<std::wstring, GameObjectMultiSprite*>::value_type(_SpriteName, pNewObjMultiSprite));

	return pNewObjMultiSprite;
}

GameObjectMultiSprite * ResourceManager::Find_MultiSprite(const wchar_t * _SpriteName)
{
	std::map<std::wstring, GameObjectMultiSprite*>::iterator Multi_Iter = m_ObjMultiSprite.find(_SpriteName);

	if (Multi_Iter == m_ObjMultiSprite.end())
	{
		return nullptr;
	}

	return Multi_Iter->second;
}

GameObjectSprite* ResourceManager::Find_Sprite(const wchar_t * _SpriteName, size_t _idx)
{
	std::map<std::wstring, GameObjectMultiSprite*>::iterator Multi_Iter = m_ObjMultiSprite.find(_SpriteName);

	if (Multi_Iter == m_ObjMultiSprite.end())
	{
		return nullptr;
	}

	return Multi_Iter->second->GetSprite(_idx);

}

///////////////////////////////////////////////////// Sound
SoundSource* ResourceManager::Sound_Load(const wchar_t* _Folder, const wchar_t* _Name)
{
	SoundSource* pSoundSource = Sound_Find(_Name);

	if (nullptr != pSoundSource)
	{
		return pSoundSource;
	}

	pSoundSource = new SoundSource();

	std::wstring Path = FindPath(_Folder);
	Path += _Name;

	if (false == pSoundSource->Sound_Load(Path.c_str()))
	{
		Tassert(true);
		delete pSoundSource;
	}

	m_SoundSource.insert(std::map<std::wstring, SoundSource*>::value_type(_Name, pSoundSource));

	return pSoundSource;
}

SoundSource* ResourceManager::SoundBGM_Load(const wchar_t* _Folder, const wchar_t* _Name)
{
	SoundSource* pSoundSource = Sound_Find(_Name);

	if (nullptr != pSoundSource)
	{
		return pSoundSource;
	}

	pSoundSource = new SoundSource();

	std::wstring Path = FindPath(_Folder);
	Path += _Name;

	if (false == pSoundSource->SoundBGM_Load(Path.c_str()))
	{
		Tassert(true);
		delete pSoundSource;
	}

	m_SoundSource.insert(std::map<std::wstring, SoundSource*>::value_type(_Name, pSoundSource));

	return pSoundSource;
}

SoundSource* ResourceManager::Sound_Find(const wchar_t* _Name)
{
	std::map<std::wstring, SoundSource*>::iterator Find_Iter = m_SoundSource.find(_Name);

	if (Find_Iter == m_SoundSource.end())
	{
		return nullptr;
	}

	return Find_Iter->second;
}

void ResourceManager::Sound_Paly(const wchar_t* _Name)
{
	SoundSource* pSoundSource = Sound_Find(_Name);

	Tassert(nullptr == pSoundSource);

	if (nullptr == pSoundSource)
	{
		return;
	}

	m_pSoundSystem->playSound(pSoundSource->Get_Sound(), nullptr, false, nullptr);
}


SoundControl* ResourceManager::SoundControl_Insert()
{
	SoundControl* NewControl = new SoundControl();
	m_SoundControl.insert(NewControl);
	return NewControl;
}

bool ResourceManager::SoundControl_Erase(SoundControl* _SoundControl)
{
	std::set<SoundControl*>::iterator Find_Iter = m_SoundControl.find(_SoundControl);

	if (m_SoundControl.end() == Find_Iter)
	{
		return false;
	}

	delete *Find_Iter;
	m_SoundControl.erase(Find_Iter);

	return true;
}