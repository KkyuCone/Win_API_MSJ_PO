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

	AnimationRenderer* m_MapSelectVilage;		// �� ����Ʈ ��� - Vilage
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

	ObjectCollision* m_MapSelectCheckCol;			// �� ����ȭ�� - Ȯ��
	ObjectCollision* m_MapSelectCancleCol;			// �� ����ȭ�� - ���

	ObjectCollision* m_MapSelectVilageCol;			// �� ����ȭ�� - ������
	ObjectCollision* m_MapSelectPirateCol;			// �� ����ȭ�� - ��Ʈ��
	ObjectCollision* m_MapSelectCookieCol;			// �� ����ȭ�� - ��Ű
	ObjectCollision* m_MapSelectIceCol;				// �� ����ȭ�� - ���̽�
	ObjectCollision* m_MapSelectForestCol;			// �� ����ȭ�� - ������Ʈ
	ObjectCollision* m_MapSelectDesertCol;			// �� ����ȭ�� - ����Ʈ

	ObjectCollision* m_MapSelectButton;				// �� ���� ��ư

	ObjectCollision* m_GameStartButton;				// ���� ��ŸƮ ��ư

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
	// ������Ʈ
	virtual void Start_Update() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void DebugRender() override;


public:
	// �浹
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) override;


public:
	// ��Ÿ �Լ�
	void Change_CharacterSelect(std::wstring _Name);
	void Change_CharacterImage(std::wstring _Name);
	void Show_CharacterInformation(std::wstring _Name);

	void ShowMapSelectScreen(ObjectCollision* _This);				// �� ����â ����, ����
	void SelectMapName(std::wstring _Name);				// �� �̸� ����
	void ClickMapNameButton(ObjectCollision* _This);		// �� ��� Ŭ���� ��� �̹��� ��ȭ
	void SelectMapImageChange(std::wstring _Name);		// ���õ� �� �̹��� �����ֱ�

	void StartGame();								// ���� ���� (�÷��� ȭ������ �̵�)
	void Change_CharacterType(std::wstring _ChangeName);
};

