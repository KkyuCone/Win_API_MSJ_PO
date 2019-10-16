#include "stdafx.h"
#include "Select_Character1P.h"
#include "AnimationRenderer.h"
#include "ObjectCollision.h"
#include "MainSceneState.h"
#include "ResourceManager.h"
#include "SoundControl.h"
#include "Player.h"


Select_Character1P::Select_Character1P()
	: m_CharacterSelect(nullptr), m_CharacterInformation(nullptr), m_ShowCharacter(nullptr)
	, m_MapSelectBackground(nullptr), m_MapMainImage(nullptr)
	, m_MapSelectVilage(nullptr), m_MapSelectPirate(nullptr), m_MapSelectForest(nullptr), m_MapSelectCookie(nullptr), m_MapSelectIce(nullptr)
	, m_MapSelectShowIamage(nullptr)
	, m_SelectMapName(L"")
{
	m_SoundControl = ResourceManager::Instance().SoundControl_Insert();
}


Select_Character1P::~Select_Character1P()
{
}

////////////////////////////////////////////// 업데이트

void Select_Character1P::Start_Update()
{
	Stage()->DebugCol_Off();

	// 캐릭터 선택하기
	m_CharacterSelect = Create_Renderer<AnimationRenderer>();
	//m_CharacterSelect->Size(F_Position{298, 313});
	m_CharacterSelect->Size(F_Position{ 380, 403 });
	m_CharacterSelect->Pivot(F_Position{ 805, 215 });
	m_CharacterSelect->Animation_Create(L"Bazzi", L"Character_Select.bmp", 0, 0, false);
	m_CharacterSelect->Animation_Create(L"Dao", L"Character_Select.bmp", 1, 1, false);
	m_CharacterSelect->Animation_Create(L"Marid", L"Character_Select.bmp", 2, 2, false);
	m_CharacterSelect->Animation_Create(L"Cappy", L"Character_Select.bmp", 3, 3, false);
	m_CharacterSelect->Animation_Change(L"Bazzi");

	// 캐릭터 정보
	m_CharacterInformation = Create_Renderer<AnimationRenderer>();
	m_CharacterInformation->Size(F_Position{ 200, 136 });
	m_CharacterInformation->Pivot(F_Position{ 520, 200 });
	m_CharacterInformation->Animation_Create(L"Bazzi", L"Character_Information.bmp", 0, 0, false);
	m_CharacterInformation->Animation_Create(L"Dao", L"Character_Information.bmp", 1, 1, false);
	m_CharacterInformation->Animation_Create(L"Marid", L"Character_Information.bmp", 2, 2, false);
	m_CharacterInformation->Animation_Create(L"Cappy", L"Character_Information.bmp", 3, 3, false);
	m_CharacterInformation->Animation_Create(L"Empty_Infomation", L"Character_Information.bmp", 4, 4, false);
	m_CharacterInformation->Animation_Change(L"Empty_Infomation");

	// 캐릭터 이미지
	m_ShowCharacter = Create_Renderer<AnimationRenderer>(2);
	m_ShowCharacter->Size(F_Position{ 100, 100 });
	m_ShowCharacter->Pivot(F_Position{ 80, 185 });
	m_ShowCharacter->Animation_Create(L"Bazzi", L"unit_bazzi.bmp", 5, 5, false);
	m_ShowCharacter->Animation_Create(L"Dao", L"unit_dao.bmp", 5, 5, false);
	m_ShowCharacter->Animation_Create(L"Marid", L"unit_luxmarid.bmp", 5, 5, false);
	m_ShowCharacter->Animation_Create(L"Cappy", L"unit_cappy.bmp", 5, 5, false);
	m_ShowCharacter->Animation_Change(L"Bazzi");

	// 맵선택 배경이미지
	m_MapSelectBackground = Create_Renderer<AnimationRenderer>(3);
	m_MapSelectBackground->Size(F_Position{ 692, 634 });
	m_MapSelectBackground->Pivot(F_Position{ 1024/2, 768/2 });
	m_MapSelectBackground->Animation_Create(L"MapSelectBackground", L"MapSelectBackground.bmp", 0, 0, false);
	m_MapSelectBackground->Animation_Create(L"MapSelectBackground_Empty", L"MapSelectBackground.bmp", 1, 1, false);
	m_MapSelectBackground->Animation_Change(L"MapSelectBackground_Empty");

	// 선택된 맵 이미지
	m_MapMainImage = Create_Renderer<AnimationRenderer>(3);
	m_MapMainImage->Size(F_Position{ 150, 130 });
	m_MapMainImage->Pivot(F_Position{ 295, 270 });
	m_MapMainImage->Animation_Create(L"MapMainImage_None", L"MapMainImage.bmp", 6, 6, false);
	m_MapMainImage->Animation_Create(L"MapMainImage_Cookie", L"MapMainImage.bmp", 0, 0, false);
	m_MapMainImage->Animation_Create(L"MapMainImage_Vilage", L"MapMainImage.bmp", 1, 1, false);
	m_MapMainImage->Animation_Create(L"MapMainImage_Desert", L"MapMainImage.bmp", 2, 2, false);
	m_MapMainImage->Animation_Create(L"MapMainImage_Forest", L"MapMainImage.bmp", 3, 3, false);
	m_MapMainImage->Animation_Create(L"MapMainImage_Ice", L"MapMainImage.bmp", 4, 4, false);
	m_MapMainImage->Animation_Create(L"MapMainImage_Pirate", L"MapMainImage.bmp", 5, 5, false);
	m_MapMainImage->Animation_Change(L"MapMainImage_None");

	// 맵선택 - 맵목록
	m_MapSelectVilage = Create_Renderer<AnimationRenderer>(4);			// 빌리지
	m_MapSelectVilage->Size(F_Position{ 310, 18 });
	m_MapSelectVilage->Pivot(F_Position{ 585, 240 });
	m_MapSelectVilage->Animation_Create(L"Vilage_None", L"MapSelectName.bmp", 0, 0, false);
	m_MapSelectVilage->Animation_Create(L"Vilage_Select", L"MapSelectName.bmp", 1, 1, false);
	m_MapSelectVilage->Animation_Create(L"Vilage_Empty", L"MapSelectName.bmp", 12, 12, false);
	m_MapSelectVilage->Animation_Change(L"Vilage_Empty");

	m_MapSelectPirate = Create_Renderer<AnimationRenderer>(4);			// 패트릿
	m_MapSelectPirate->Size(F_Position{ 310, 18 });
	m_MapSelectPirate->Pivot(F_Position{ 585, 260 });
	m_MapSelectPirate->Animation_Create(L"Pirate_None", L"MapSelectName.bmp", 2, 2, false);
	m_MapSelectPirate->Animation_Create(L"Pirate_Select", L"MapSelectName.bmp", 3, 3, false);
	m_MapSelectPirate->Animation_Create(L"Pirate_Empty", L"MapSelectName.bmp", 12, 12, false);
	m_MapSelectPirate->Animation_Change(L"Pirate_Empty");

	m_MapSelectCookie = Create_Renderer<AnimationRenderer>(4);			// 쿠키
	m_MapSelectCookie->Size(F_Position{ 310, 18 });
	m_MapSelectCookie->Pivot(F_Position{ 585, 280 });
	m_MapSelectCookie->Animation_Create(L"Cookie_None", L"MapSelectName.bmp", 4, 4, false);
	m_MapSelectCookie->Animation_Create(L"Cookie_Select", L"MapSelectName.bmp", 5, 5, false);
	m_MapSelectCookie->Animation_Create(L"Cookie_Empty", L"MapSelectName.bmp", 12, 12, false);
	m_MapSelectCookie->Animation_Change(L"Cookie_Empty");

	m_MapSelectIce = Create_Renderer<AnimationRenderer>(4);			// 아이스
	m_MapSelectIce->Size(F_Position{ 310, 18 });
	m_MapSelectIce->Pivot(F_Position{ 585, 300 });
	m_MapSelectIce->Animation_Create(L"Ice_None", L"MapSelectName.bmp", 6, 6, false);
	m_MapSelectIce->Animation_Create(L"Ice_Select", L"MapSelectName.bmp", 7, 7, false);
	m_MapSelectIce->Animation_Create(L"Ice_Empty", L"MapSelectName.bmp", 12, 12, false);
	m_MapSelectIce->Animation_Change(L"Ice_Empty");

	m_MapSelectForest = Create_Renderer<AnimationRenderer>(4);		// 포레스트
	m_MapSelectForest->Size(F_Position{ 310, 18 });
	m_MapSelectForest->Pivot(F_Position{ 585, 320 });
	m_MapSelectForest->Animation_Create(L"Forest_None", L"MapSelectName.bmp", 8, 8, false);
	m_MapSelectForest->Animation_Create(L"Forest_Select", L"MapSelectName.bmp", 9, 9, false);
	m_MapSelectForest->Animation_Create(L"Forest_Empty", L"MapSelectName.bmp", 12, 12, false);
	m_MapSelectForest->Animation_Change(L"Forest_Empty");

	m_MapSelectDesert = Create_Renderer<AnimationRenderer>(4);		// 데저트
	m_MapSelectDesert->Size(F_Position{ 310, 18 });
	m_MapSelectDesert->Pivot(F_Position{ 585, 340 });
	m_MapSelectDesert->Animation_Create(L"Desert_None", L"MapSelectName.bmp", 10, 10, false);
	m_MapSelectDesert->Animation_Create(L"Desert_Select", L"MapSelectName.bmp", 11, 11, false);
	m_MapSelectDesert->Animation_Create(L"Desert_Empty", L"MapSelectName.bmp", 12, 12, false);
	m_MapSelectDesert->Animation_Change(L"Desert_Empty");

	// 대기방 - 선택된 맵 이미지 보여주기
	m_MapSelectShowIamage = Create_Renderer<AnimationRenderer>(0);
	m_MapSelectShowIamage->Size(F_Position{ 150, 130 });
	m_MapSelectShowIamage->Pivot(F_Position{ 721, 530 });
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_None", L"MapMainImage.bmp", 6, 6, false);
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_Cookie", L"MapMainImage.bmp", 0, 0, false);
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_Vilage", L"MapMainImage.bmp", 1, 1, false);
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_Desert", L"MapMainImage.bmp", 2, 2, false);
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_Forest", L"MapMainImage.bmp", 3, 3, false);
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_Ice", L"MapMainImage.bmp", 4, 4, false);
	m_MapSelectShowIamage->Animation_Create(L"MapMainImage_Pirate", L"MapMainImage.bmp", 5, 5, false);
	m_MapSelectShowIamage->Animation_Change(L"MapMainImage_None");


	// 캐릭터 선택정보 Collision
	m_BazziCol = Create_Collision(L"BazziSelect");
	m_BazziCol->Name = L"Bazzi";
	m_BazziCol->Pivot(F_Position{ 759, 233 });
	m_BazziCol->Size(F_Position{ 83.5f, 55 });

	m_DaoCol = Create_Collision(L"DaoSelect");
	m_DaoCol->Name = L"Dao";
	m_DaoCol->Pivot(F_Position{ 667, 174 });
	m_DaoCol->Size(F_Position{ 83.5f, 55 });

	m_MaridCol = Create_Collision(L"MaridSelect");
	m_MaridCol->Name = L"Marid";
	m_MaridCol->Pivot(F_Position{ 667, 233 });
	m_MaridCol->Size(F_Position{ 83.5f, 55 });

	m_CappyCol = Create_Collision(L"CappySelect");
	m_CappyCol->Name = L"Cappy";
	m_CappyCol->Pivot(F_Position{ 942, 233 });
	m_CappyCol->Size(F_Position{ 83.5f, 55 });


	// 맵관련
	m_MapSelectCheckCol = Create_Collision(L"MapSelectCheck");		// 확인
	m_MapSelectCheckCol->Name = L"MapSelectCheck";
	m_MapSelectCheckCol->Pivot(F_Position{ 436, 660 });
	m_MapSelectCheckCol->Size(F_Position{ 134, 40 });
	m_MapSelectCheckCol->Off();
	m_MapSelectCheckCol->Object()->Off();

	m_MapSelectCancleCol = Create_Collision(L"MapSelectCancle");	// 취소
	m_MapSelectCancleCol->Name = L"MapSelectCancle";
	m_MapSelectCancleCol->Pivot(F_Position{ 587, 660 });
	m_MapSelectCancleCol->Size(F_Position{ 134, 40 });
	m_MapSelectCancleCol->Off();
	m_MapSelectCancleCol->Object()->Off();

	m_MapSelectVilageCol = Create_Collision(L"MapSelectVilage");		// Vilage
	m_MapSelectVilageCol->Name = L"MapSelectVilage";
	m_MapSelectVilageCol->Size(F_Position{ 310, 18 });
	m_MapSelectVilageCol->Pivot(F_Position{ 585, 240 });
	m_MapSelectVilageCol->Off();
	m_MapSelectVilageCol->Object()->Off();

	m_MapSelectPirateCol = Create_Collision(L"MapSelectPirate");
	m_MapSelectPirateCol->Name = L"MapSelectPirate";
	m_MapSelectPirateCol->Size(F_Position{ 310, 18 });
	m_MapSelectPirateCol->Pivot(F_Position{ 585, 260 });
	m_MapSelectPirateCol->Off();
	m_MapSelectPirateCol->Object()->Off();

	m_MapSelectCookieCol = Create_Collision(L"MapSelectCookie");
	m_MapSelectCookieCol->Name = L"MapSelectCookie";
	m_MapSelectCookieCol->Size(F_Position{ 310, 18 });
	m_MapSelectCookieCol->Pivot(F_Position{ 585, 280 });
	m_MapSelectCookieCol->Off();
	m_MapSelectCookieCol->Object()->Off();

	m_MapSelectIceCol = Create_Collision(L"MapSelectIce");
	m_MapSelectIceCol->Name = L"MapSelectIce";
	m_MapSelectIceCol->Size(F_Position{ 310, 18 });
	m_MapSelectIceCol->Pivot(F_Position{ 585, 300 });
	m_MapSelectIceCol->Off();

	m_MapSelectForestCol = Create_Collision(L"MapSelectForest");
	m_MapSelectForestCol->Name = L"MapSelectForest";
	m_MapSelectForestCol->Size(F_Position{ 310, 18 });
	m_MapSelectForestCol->Pivot(F_Position{ 585, 320 });
	m_MapSelectForestCol->Off();

	m_MapSelectDesertCol = Create_Collision(L"MapSelectDesert");
	m_MapSelectDesertCol->Name = L"MapSelectDesert";
	m_MapSelectDesertCol->Size(F_Position{ 310, 18 });
	m_MapSelectDesertCol->Pivot(F_Position{ 585, 340 });
	m_MapSelectDesertCol->Off();
	m_MapSelectDesertCol->Object()->Off();

	m_MapSelectButton = Create_Collision(L"MapSelectButton");		// 맵선택 버튼
	m_MapSelectButton->Name = L"MapSelectButton";
	m_MapSelectButton->Size(F_Position{ 160, 70 });
	m_MapSelectButton->Pivot(F_Position{ 905, 580 });
	m_MapSelectButton->Object()->Off();

	m_GameStartButton = Create_Collision(L"GameStartButton");		// 게임시작버튼 버튼
	m_GameStartButton->Name = L"GameStartButton";
	m_GameStartButton->Size(F_Position{ 240, 70 });
	m_GameStartButton->Pivot(F_Position{ 780, 670 });
	m_GameStartButton->Object()->Off();
}

void Select_Character1P::Update()
{

}

void Select_Character1P::Late_Update()
{
}

void Select_Character1P::DebugRender()
{

}

////////////////////////////////////////////// 충돌

void Select_Character1P::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_Other->Name == L"MouseCursor")
	{
		Show_CharacterInformation(_This->Name);
	}
}

void Select_Character1P::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{
	// 선택화면
	if (true == InputManager::Instance().Down(L"MouseDown"))
	{
		if (_Other->Name == L"MouseCursor")
		{
			Change_CharacterSelect(_This->Name);
			Change_CharacterImage(_This->Name);
			ShowMapSelectScreen(_This);
			ClickMapNameButton(_This);

			if (_This->Name == L"GameStartButton")
			{
				StartGame();
			}
		}
	}
}

void Select_Character1P::Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_Other->Name == L"MouseCursor")
	{
		Show_CharacterInformation(L"Empty_Infomation");
	}
}


////////////////////////////////////////////// 기타함수
void Select_Character1P::Change_CharacterSelect(std::wstring _Name)
{
	if (L"Bazzi" == _Name || L"Dao" == _Name || L"Marid" == _Name || L"Cappy" == _Name)
	{
		m_CharacterSelect->Animation_Change(_Name.c_str());

		m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
		m_SoundControl->Sound_SetPitch(1.0f);
	}
}

void Select_Character1P::Change_CharacterType(std::wstring _ChangeName)
{
	if (L"Bazzi" == _ChangeName)
	{
		MainSceneState::m_GameChar_Type = MainSceneState::CharacterType::Bazzi;
	}
	else if (L"Dao" == _ChangeName)
	{
		MainSceneState::m_GameChar_Type = MainSceneState::CharacterType::Dao;
	}
	else if (L"Marid" == _ChangeName)
	{
		MainSceneState::m_GameChar_Type = MainSceneState::CharacterType::Marid;
	}
	else if (L"Cappy" == _ChangeName)
	{
		MainSceneState::m_GameChar_Type = MainSceneState::CharacterType::Cappy;
	}
}

void Select_Character1P::Change_CharacterImage(std::wstring _Name)
{
	if (L"Bazzi" == _Name || L"Dao" == _Name || L"Marid" == _Name || L"Cappy" == _Name)
	{
		m_ShowCharacter->Animation_Change(_Name.c_str());

		if (L"Empty_Infomation" != _Name)
		{
			Change_CharacterType(_Name);
		}
	}
}

void Select_Character1P::Show_CharacterInformation(std::wstring _Name)
{
	if (L"Bazzi" == _Name || L"Dao" == _Name || L"Marid" == _Name || L"Cappy" == _Name || L"Empty_Infomation" == _Name)
	{
		m_CharacterInformation->Animation_Change(_Name.c_str());
	}
}


// 맵 선택창 띄우기, 끄기
void Select_Character1P::ShowMapSelectScreen(ObjectCollision* _This)
{

	if (L"MapSelectButton" == _This->Name)
	{
		m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
		m_SoundControl->Sound_SetPitch(1.0f);

		// < 콜라이더 >
		// 맵선택과 관련되지 않는 콜라이더 끄기
		// 캐릭터 선택관련
		m_BazziCol->Off();
		m_BazziCol->Object()->Off();
		m_DaoCol->Off();
		m_DaoCol->Object()->Off();
		m_MaridCol->Off();
		m_MaridCol->Object()->Off();
		m_CappyCol->Off();
		m_CappyCol->Object()->Off();

		// 맵 선택 버튼
		m_MapSelectButton->Off();


		// 맵선택과 관련된 콜라이더 모두 켜기
		m_MapSelectCheckCol->On();		// 확인
		m_MapSelectCancleCol->On();		// 취소

		m_MapSelectVilageCol->On();		// 맵 선택화면 - 빌리지
		m_MapSelectPirateCol->On();		// 맵 선택화면 - 패트릿
		m_MapSelectCookieCol->On();		// 맵 선택화면 - 쿠키
		m_MapSelectIceCol->On();		// 맵 선택화면 - 아이스
		m_MapSelectForestCol->On();		// 맵 선택화면 - 포레스트
		m_MapSelectDesertCol->On();		// 맵 선택화면 - 데저트

		m_GameStartButton->Off();
		m_GameStartButton->Object()->Off();

		// 렌더 관련
		m_MapSelectBackground->Animation_Change(L"MapSelectBackground");
		m_MapSelectVilage->Animation_Change(L"Vilage_None");
		m_MapSelectPirate->Animation_Change(L"Pirate_None");
		m_MapSelectForest->Animation_Change(L"Forest_None");
		m_MapSelectCookie->Animation_Change(L"Cookie_None");
		m_MapSelectDesert->Animation_Change(L"Desert_None");
		m_MapSelectIce->Animation_Change(L"Ice_None");
	}
	else if (L"MapSelectCancle" == _This->Name || L"MapSelectCheck" == _This->Name)
	{
		m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
		m_SoundControl->Sound_SetPitch(1.0f);

		// < 콜라이더 >
		// 맵선택과 관련되지 않는 콜라이더 켜기
		// 캐릭터 선택관련
		m_BazziCol->On();
		m_DaoCol->On();
		m_MaridCol->On();
		m_CappyCol->On();

		// 맵 선택 버튼
		m_MapSelectButton->On();


		// 맵선택과 관련된 콜라이더 모두 끄기
		m_MapSelectCheckCol->Off();		// 확인
		m_MapSelectCheckCol->Object()->Off();
		m_MapSelectCancleCol->Off();		// 취소
		m_MapSelectCancleCol->Object()->Off();

		m_MapSelectVilageCol->Off();		// 맵 선택화면 - 빌리지
		m_MapSelectVilageCol->Object()->Off();
		m_MapSelectPirateCol->Off();		// 맵 선택화면 - 패트릿
		m_MapSelectPirateCol->Object()->Off();
		m_MapSelectCookieCol->Off();		// 맵 선택화면 - 쿠키
		m_MapSelectCookieCol->Object()->Off();
		m_MapSelectIceCol->Off();		// 맵 선택화면 - 아이스
		m_MapSelectIceCol->Object()->Off();
		m_MapSelectForestCol->Off();		// 맵 선택화면 - 포레스트
		m_MapSelectForestCol->Object()->Off();
		m_MapSelectDesertCol->Off();		// 맵 선택화면 - 데저트
		m_MapSelectDesertCol->Object()->Off();

		m_GameStartButton->On();


		// 렌더관련
		m_MapSelectBackground->Animation_Change(L"MapSelectBackground_Empty");
		m_MapSelectVilage->Animation_Change(L"Vilage_Empty");
		m_MapSelectPirate->Animation_Change(L"Pirate_Empty");
		m_MapSelectForest->Animation_Change(L"Forest_Empty");
		m_MapSelectCookie->Animation_Change(L"Cookie_Empty");
		m_MapSelectDesert->Animation_Change(L"Desert_Empty");
		m_MapSelectIce->Animation_Change(L"Ice_Empty");

		m_MapMainImage->Animation_Change(L"MapMainImage_None");

	}
}

// 맵 이름 지정
void Select_Character1P::SelectMapName(std::wstring _Name)
{
	int number = rand() % 2;		// 0 ~ 1 랜덤
	std::string Count = "";
	std::wstring Con = L"";
	Count = Count + std::to_string(number);		// 문자열로 변환
	
	m_SelectMapName = _Name + L"_0";
	m_SelectMapName += Con.assign(Count.begin(), Count.end());			// 맵이름_0+number

	if (L"Cookie" == _Name)
	{
		m_SelectMapName = L"Cookie_00";
	}
	else if (L"Vilage" == _Name)
	{
		m_SelectMapName = L"Vilage_00";
	}

	MainSceneState::SelectMapName = m_SelectMapName;
}

// 맵 목록 클릭시 목록 이미지 변화
void Select_Character1P::ClickMapNameButton(ObjectCollision* _This)
{
	m_SoundControl->Sound_NewPlay(L"ButtonClick.ogg");
	m_SoundControl->Sound_SetPitch(1.0f);

	int a = 0;
	if ( L"MapSelectVilage" == _This->Name)
	{
		m_MapSelectVilage->Animation_Change(L"Vilage_Select");

		m_MapSelectPirate->Animation_Change(L"Pirate_None");
		m_MapSelectCookie->Animation_Change(L"Cookie_None");
		m_MapSelectIce->Animation_Change(L"Ice_None");
		m_MapSelectForest->Animation_Change(L"Forest_None");
		m_MapSelectDesert->Animation_Change(L"Desert_None");

		// 선택된 맵 이미지 보여주기
		SelectMapImageChange(L"MapMainImage_Vilage");

		// 선택된 맵 이름 ( 불러올 맵 이름 변경 )
		SelectMapName(L"Vilage");
	}
	else if ( L"MapSelectPirate" == _This->Name)
	{
		m_MapSelectPirate->Animation_Change(L"Pirate_Select");

		m_MapSelectVilage->Animation_Change(L"Vilage_None");
		m_MapSelectCookie->Animation_Change(L"Cookie_None");
		m_MapSelectIce->Animation_Change(L"Ice_None");
		m_MapSelectForest->Animation_Change(L"Forest_None");
		m_MapSelectDesert->Animation_Change(L"Desert_None");

		// 선택된 맵 이미지 보여주기
		SelectMapImageChange(L"MapMainImage_Pirate");

		// 선택된 맵 이름 ( 불러올 맵 이름 변경 )
		SelectMapName(L"Pirate");
	}
	else if (L"MapSelectCookie" == _This->Name)
	{
		m_MapSelectCookie->Animation_Change(L"Cookie_Select");

		m_MapSelectVilage->Animation_Change(L"Vilage_None");
		m_MapSelectPirate->Animation_Change(L"Pirate_None");
		m_MapSelectIce->Animation_Change(L"Ice_None");
		m_MapSelectForest->Animation_Change(L"Forest_None");
		m_MapSelectDesert->Animation_Change(L"Desert_None");

		SelectMapImageChange(L"MapMainImage_Cookie");
		SelectMapName(L"Cookie");
	}
	else if (L"MapSelectIce" == _This->Name)
	{
		m_MapSelectIce->Animation_Change(L"Ice_Select");

		m_MapSelectVilage->Animation_Change(L"Vilage_None");
		m_MapSelectPirate->Animation_Change(L"Pirate_None");
		m_MapSelectCookie->Animation_Change(L"Cookie_None");
		m_MapSelectForest->Animation_Change(L"Forest_None");
		m_MapSelectDesert->Animation_Change(L"Desert_None");

		SelectMapImageChange(L"MapMainImage_Ice");
		SelectMapName(L"Ice");
	}
	else if (L"MapSelectForest" == _This->Name)
	{
		m_MapSelectForest->Animation_Change(L"Forest_Select");

		m_MapSelectVilage->Animation_Change(L"Vilage_None");
		m_MapSelectPirate->Animation_Change(L"Pirate_None");
		m_MapSelectCookie->Animation_Change(L"Cookie_None");
		m_MapSelectIce->Animation_Change(L"Ice_None");
		m_MapSelectDesert->Animation_Change(L"Desert_None");

		SelectMapImageChange(L"MapMainImage_Forest");
		SelectMapName(L"Forest");
	}
	else if (L"MapSelectDesert" == _This->Name)
	{
		m_MapSelectDesert->Animation_Change(L"Desert_Select");

		m_MapSelectVilage->Animation_Change(L"Vilage_None");
		m_MapSelectPirate->Animation_Change(L"Pirate_None");
		m_MapSelectCookie->Animation_Change(L"Cookie_None");
		m_MapSelectIce->Animation_Change(L"Ice_None");
		m_MapSelectForest->Animation_Change(L"Forest_None");

		SelectMapImageChange(L"MapMainImage_Desert");
		SelectMapName(L"Desert");
	}
}

// 선택된 맵 이미지 보여주기
void Select_Character1P::SelectMapImageChange( std::wstring _Name)
{
	m_MapMainImage->Animation_Change(_Name.c_str());
	m_MapSelectShowIamage->Animation_Change(_Name.c_str());
}


// 게임 스타트 ( 맵 이름 보내주기 )
void Select_Character1P::StartGame()
{
	Util_Core::Instance().ChangeStage(ALLSTAGE::PLAY);
}

