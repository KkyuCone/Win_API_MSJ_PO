#include "stdafx.h"
#include "Item.h"
#include "AnimationRenderer.h"
#include "ResourceManager.h"
#include "ObjectCollision.h"

////////////////////////////////////////////////////

Item::Item() : m_pItemAniRenderer(nullptr), m_bOwner(false), m_BombValue(0)
{
	++ItemCount;
}


Item::~Item()
{
	--ItemCount;
}

int Item::ItemCount = 0;


/////////////////////////////////////////////////////


void Item::Start_Update()
{
	// 충돌
	m_ItemCol = Create_Collision(L"Item");
	m_ItemCol->Pivot({ 0,0 });
	m_ItemCol->Size({ 0, 0 });

	// 그림자 렌더
	AnimationRenderer* m_ItemShadowRender;
	m_ItemShadowRender = Create_Renderer<AnimationRenderer>(11);
	m_ItemShadowRender->Set_Alpha(150);
	m_ItemShadowRender->Pivot(F_Position{0,-15});
	m_ItemShadowRender->Size(F_Position{ 80, 80 });
	m_ItemShadowRender->Animation_Create(L"ItemShadow", L"PlayerShadow.bmp", 0, 0, true);
	m_ItemShadowRender->Animation_Change(L"ItemShadow");


	// 렌더
	m_pItemAniRenderer = Create_Renderer<AnimationRenderer>(11);
	m_pItemAniRenderer->Size(F_Position{ 0, 0 });
	m_pItemAniRenderer->Animation_Create(L"Empty_Item", L"item_032.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Gold_Coin", L"item_033.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Silver_Coin", L"item_034.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Bronze_Coin", L"item_035.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Gold_CoinPurse", L"item_036.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Silver_CoinPurse", L"item_037.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Bronze_CoinPurse", L"item_038.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Water_Balloon", L"item_039.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Potion", L"item_040.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"MegaBomb", L"item_041.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"RollerSkates", L"item_042.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Devil", L"item_043.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Radio", L"item_044.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Owl", L"item_045.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Shild", L"item_046.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Spaceship", L"item_047.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Needle", L"item_048.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Turtle", L"item_049.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Sneakers", L"item_050.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Gloves", L"item_051.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Super", L"item_052.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"RedDevil", L"item_053.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"MonkeySpanner", L"item_054.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Spring_Sleeper", L"item_055.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Poison_Potion", L"item_056.bmp", 0, 2, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Can", L"item_057.bmp", 0, 2, true, 0.5f);

	m_pItemAniRenderer->Animation_Create(L"Shild_Get", L"item_046.bmp", 0, 0, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Needle_Get", L"item_048.bmp", 0, 0, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"MonkeySpanner_Get", L"item_054.bmp", 0, 0, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Spring_Sleeper_Get", L"item_055.bmp", 0, 0, true, 0.5f);
	m_pItemAniRenderer->Animation_Create(L"Can_Get", L"item_057.bmp", 0, 0, true, 0.5f);
}

void Item::Prev_Update()
{

}

void Item::Update()
{

}

void Item::Late_Update()
{

}



// 아이템 만들기(이미지교체)
void Item::Change_ItemImage(std::wstring _Name, ITEM_TYPE _Type)
{
	switch (_Type)
	{
	case Item::Emtpy_Item:
		m_pItemAniRenderer->Size(F_Position{ 44, 44 });
		m_ItemCol->Size(F_Position{ 33, 34 });
		break;
	case Item::Gold_Coin:
		m_pItemAniRenderer->Size(F_Position{ 44, 44 });
		m_ItemCol->Size(F_Position{ 33, 34 });
	case Item::Silver_Coin:
	case Item::Bronze_Coin:
		m_pItemAniRenderer->Size(F_Position{ 33, 34 });
		m_ItemCol->Size(F_Position{ 33, 34 });
		break;
	case Item::Gold_CoinPurse:
	case Item::Silver_CoinPurse:
	case Item::Bronze_CoinPurse:
		m_pItemAniRenderer->Size(F_Position{ 45, 50 });
		m_ItemCol->Size(F_Position{ 45, 50 });
		break;
	case Item::Water_Balloon:
		m_pItemAniRenderer->Size(F_Position{ 44, 51 });
		m_ItemCol->Size(F_Position{ 44, 51 });
		break;
	case Item::Potion:
		m_pItemAniRenderer->Size(F_Position{ 44, 50 });
		m_ItemCol->Size(F_Position{ 44, 50 });
		break;
	case Item::MegaBomb:
		m_pItemAniRenderer->Size(F_Position{ 55, 56 });
		m_ItemCol->Size(F_Position{ 55, 56 });
		break;
	case Item::RollerSkates:
		m_pItemAniRenderer->Size(F_Position{ 49, 54 });
		m_ItemCol->Size(F_Position{ 49, 54 });
		break;
	/*case Item::Devil:
		m_pItemAniRenderer->Size(F_Position{ 47, 48 });
		m_ItemCol->Size(F_Position{ 47, 48 });
		break;
	case Item::Radio:
		m_pItemAniRenderer->Size(F_Position{ 49, 53 });
		m_ItemCol->Size(F_Position{ 49, 53 });
		break;
	case Item::Owl:
		m_pItemAniRenderer->Size(F_Position{ 44, 48 });
		m_ItemCol->Size(F_Position{ 44, 48 });
		break;
	case Item::Shild:
		m_pItemAniRenderer->Size(F_Position{ 48, 48 });
		m_ItemCol->Size(F_Position{ 48, 48 });
		break;
	case Item::Spaceship:
		m_pItemAniRenderer->Size(F_Position{ 49, 52 });
		m_ItemCol->Size(F_Position{ 49, 52 });
		break;*/
	case Item::Needle:
		m_pItemAniRenderer->Size(F_Position{ 44, 44 });
		m_ItemCol->Size(F_Position{ 44, 44 });
		break;
	/*case Item::Turtle:
		m_pItemAniRenderer->Size(F_Position{ 47, 52 });
		m_ItemCol->Size(F_Position{ 47, 52 });
		break;*/
	case Item::Sneakers:
		m_pItemAniRenderer->Size(F_Position{ 49, 53 });
		m_ItemCol->Size(F_Position{ 49, 53 });
		break;
	/*case Item::Gloves:
		m_pItemAniRenderer->Size(F_Position{ 35, 43 });
		m_ItemCol->Size(F_Position{ 35, 43 });
		break;
	case Item::Super:
		m_pItemAniRenderer->Size(F_Position{ 42, 47 });
		m_ItemCol->Size(F_Position{ 42, 47 });
		break;*/
	case Item::RedDevil:
		m_pItemAniRenderer->Size(F_Position{ 47, 48 });
		m_ItemCol->Size(F_Position{ 47, 48 });
		break;
	/*case Item::MonkeySpanner:
		m_pItemAniRenderer->Size(F_Position{ 44, 50 });
		m_ItemCol->Size(F_Position{ 44, 50 });
		break;
	case Item::Spring_Sleeper:
		m_pItemAniRenderer->Size(F_Position{ 54, 54 });
		m_ItemCol->Size(F_Position{ 54, 54 });
		break;
	case Item::Poison_Potion:
		m_pItemAniRenderer->Size(F_Position{ 48, 48 });
		m_ItemCol->Size(F_Position{ 48, 48 });
		break;
	case Item::Can:
		m_pItemAniRenderer->Size(F_Position{ 48, 48 });
		m_ItemCol->Size(F_Position{ 48, 48 });
		break;*/
	default:
		break;
	}

	m_ItemCol->Name = _Name;

	if (true == m_bOwner)
	{
		//// 소유주가 있다면 
		if (m_ItemCol->IsObjDeath() == false)
		{
			m_ItemCol->Obj_Death();
		}

		m_pItemAniRenderer->Pivot({ 887,655 });
	}
	else
	{
		m_ItemCol->Pivot({ 0,-10.0f });
		m_pItemAniRenderer->Pivot({ 0,-10.0f });
	}

	const wchar_t* aniName = _Name.c_str();

	m_pItemAniRenderer->Animation_Change(aniName);
}


void Item::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_Other->Name == L"Bomb")
	{
		++m_BombValue;

		if (2 <= m_BombValue)
		{
			Obj_Death();
		}
	}
}