#pragma once
#include "ObjectRenderer.h"
#include "ObjNameBase.h"

class GameObjectSprite;
class GameObjectMultiSprite;
class AnimationRenderer : public ObjectRenderer
{
private:
	class Ani : public ObjNameBase
	{
	private:
		GameObjectMultiSprite* m_pMultiobjSprite;
		size_t m_AniStart;
		size_t m_AniEnd;
		size_t m_AniCur;		// 현재 애니메이션
		float m_CurTime;
		float m_ChangeTime;
		bool m_bLoop;

	public:
		void Ani_Update();
		void Ani_Start(size_t _Start);
		GameObjectSprite* Get_CurSprite();
		bool IsAniEnd();

	public:
		Ani(GameObjectMultiSprite* _pObjMultiSPrite, 
			size_t _AniStart, 
			size_t _AniEnd, 
			float _AniChangeTime, 
			bool _bLoop);
		~Ani();

	private:
	};

private:
	std::map<std::wstring, Ani*> m_Animations;
	Ani* m_CurAnimation;

public:
	void Animation_Create(const wchar_t* _AniName
		, const wchar_t* _MultiSpriteName
		, size_t _Start, size_t _End
		, bool _Loop = true, float Delay = 0.1f);

	void Animation_Change(const wchar_t* _AniName, size_t _idx = 0);

	bool IsCurAnimation(const wchar_t* _AniName);
	bool IsEndAnimation(const wchar_t * _AniName);
	bool IsEndAnimation();

private:
	Ani* Find_Animation(const wchar_t* _AniName);



public:
	void Render() override;

public:
	AnimationRenderer();
	~AnimationRenderer();
};

