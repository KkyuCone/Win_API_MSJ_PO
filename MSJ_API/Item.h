#pragma once
#include "ActorObjBase.h"

struct OwnerItem
{
	bool m_bItem = false;
};


class AnimationRenderer;
class ObjectCollision;
class Item : public ActorObjBase
{
public:
	friend class MainSceneState;

private:
	bool m_bOwner;
	int m_BombValue;

public:
	static int ItemCount;
	void Owner(bool _Owner)
	{
		m_bOwner = _Owner;
	}

public:
	OwnerItem ItemState;

public:
	bool EnabledItem()
	{
		return ItemState.m_bItem;
	}

public:
	enum ITEM_TYPE
	{
		Emtpy_Item = 0,
		Gold_Coin,
		Silver_Coin,
		Bronze_Coin,
		Gold_CoinPurse,
		Silver_CoinPurse,
		Bronze_CoinPurse,
		Water_Balloon,
		Potion,
		MegaBomb,
		RollerSkates,
		Needle,
		Sneakers,
		RedDevil
	};

private:
	AnimationRenderer* m_pItemAniRenderer;
	ObjectCollision* m_ItemCol;

private:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;



public:
	void Change_ItemImage(std::wstring _Name, ITEM_TYPE _Type = Emtpy_Item);

public:
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;

public:
	Item();
	~Item();
};

