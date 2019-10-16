#pragma once
#include "ActorObjBase.h"
#include <string>

class AnimationRenderer;
class ObjectCollision;
class SoundControl;
class Select_Character1P : public ActorObjBase
{
public:
	friend class MainSceneState;
private:
	std::wstring m_SelectMapName;
private:
	AnimationRenderer* m_CharacterSelect;
	AnimationRenderer* m_CharacterInformation;
	AnimationRenderer* m_ShowCharacter;
	AnimationRenderer* m_MapSelectBackground;
	AnimationRenderer* m_MapMainImage;

	AnimationRenderer* m_MapSelectVilage;		// 맵 리스트 목록 - Vilage
	AnimationRenderer* m_MapSelectPirate;
	AnimationRenderer* m_MapSelectForest;
	AnimationRenderer* m_MapSelectCookie;
	AnimationRenderer* m_MapSelectDesert;
	AnimationRenderer* m_MapSelectIce;

	AnimationRenderer* m_MapSelectShowIamage;

	ObjectCollision* m_BazziCol;
	ObjectCollision* m_DaoCol;
	ObjectCollision* m_MaridCol;
	ObjectCollision* m_CappyCol;

	ObjectCollision* m_MapSelectCheckCol;			// 맵 선택화면 - 확인
	ObjectCollision* m_MapSelectCancleCol;			// 맵 선택화면 - 취소

	ObjectCollision* m_MapSelectVilageCol;			// 맵 선택화면 - 빌리지
	ObjectCollision* m_MapSelectPirateCol;			// 맵 선택화면 - 패트릿
	ObjectCollision* m_MapSelectCookieCol;			// 맵 선택화면 - 쿠키
	ObjectCollision* m_MapSelectIceCol;				// 맵 선택화면 - 아이스
	ObjectCollision* m_MapSelectForestCol;			// 맵 선택화면 - 포레스트
	ObjectCollision* m_MapSelectDesertCol;			// 맵 선택화면 - 데저트

	ObjectCollision* m_MapSelectButton;				// 맵 선택 버튼

	ObjectCollision* m_GameStartButton;				// 게임 스타트 버튼

private:
	SoundControl* m_SoundControl;

public:
	enum SelectButtonState
	{
		ON,
		OFF,
		EMPTY
	};

public:
	Select_Character1P();
	~Select_Character1P();

public:
	// 업데이트
	virtual void Start_Update() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void DebugRender() override;


public:
	// 충돌
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) override;


public:
	// 기타 함수
	void Change_CharacterSelect(std::wstring _Name);
	void Change_CharacterImage(std::wstring _Name);
	void Show_CharacterInformation(std::wstring _Name);

	void ShowMapSelectScreen(ObjectCollision* _This);				// 맵 선택창 띄우기, 끄기
	void SelectMapName(std::wstring _Name);				// 맵 이름 지정
	void ClickMapNameButton(ObjectCollision* _This);		// 맵 목록 클릭시 목록 이미지 변화
	void SelectMapImageChange(std::wstring _Name);		// 선택된 맵 이미지 보여주기

	void StartGame();								// 게임 시작 (플레이 화면으로 이동)
	void Change_CharacterType(std::wstring _ChangeName);
};

