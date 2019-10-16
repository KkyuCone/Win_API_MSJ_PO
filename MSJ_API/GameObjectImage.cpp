#include "stdafx.h"
#include "GameObjectImage.h"
#include "Util_Core.h"
#include "BinaryReadStream.h"


/////////////////////////////////////////////////

GameObjectImage::GameObjectImage()
	: m_ImageDC(nullptr)
	, m_hLoadBitmap(nullptr)
	, m_hObjBitmap(nullptr)
	, m_TransColor(0)
	, m_bAlpha(false)
{
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}


GameObjectImage::~GameObjectImage()
{
	DeleteObject(m_hLoadBitmap);
	DeleteDC(m_ImageDC);
}

//////////////////////////////////////////////////

COLORREF GameObjectImage::GetPixelColor(int _X, int _Y)
{
	return GetPixel(m_ImageDC, _X, _Y);
}


void GameObjectImage::SetPixelColor(int _X, int _Y, COLORREF _Color)
{
	SetPixel(m_ImageDC, _X, _Y, _Color);
}

// 빈 이미지
bool GameObjectImage::Create_EmptyImage(F_Size _Size)
{
	Tassert(nullptr == Util_Core::Instance().WINDOW_INSTANCE());

	m_ImageDC = CreateCompatibleDC(Util_Core::Instance().WINDOW_DC());
	Tassert(nullptr == m_ImageDC);

	m_hObjBitmap = CreateCompatibleBitmap(Util_Core::Instance().WINDOW_DC(), _Size.IntX(), _Size.IntY());
	Tassert(nullptr == m_hObjBitmap);

	m_hLoadBitmap = (HBITMAP)SelectObject(m_ImageDC, m_hObjBitmap);
	GetObject(m_hObjBitmap, sizeof(BITMAP), &m_BitmapInfo);

	return true;
}

bool GameObjectImage::Resource_Load(const wchar_t * _Path)
{
	Tassert(nullptr == Util_Core::Instance().WINDOW_INSTANCE());

	// 이미지 로드
	m_hLoadBitmap = (HBITMAP)LoadImageW(Util_Core::Instance().WINDOW_INSTANCE(), _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	Tassert(nullptr == Util_Core::Instance().WINDOW_INSTANCE());

	// 이미지를 못찾았다면(해당 경로에 이미지가 없다면)
	if (nullptr == m_hLoadBitmap)
	{
		return false;
	}

	// 로드된 핸들을 통해 실제로 렌더링 할 수 있는 HDC를 만들어야함.
	// 윈도우 DC에 렌더링 할 수 있는 DC를 만들어 낸다.
	// 만들어지는 순간 내부에 1*1 비트맵 이미지가 만들어진다.
	m_ImageDC = CreateCompatibleDC(Util_Core::Instance().WINDOW_DC());
	Tassert(nullptr == m_ImageDC);

	// 내부에 있는 1*1 이미지를 내가 로드한 이미지로 교체
	m_hObjBitmap = (HBITMAP)SelectObject(m_ImageDC, m_hLoadBitmap);

	// 이 함수는 이미지파일의 정보를 가져온것이 아니라 로드되어 램에 올라갔을 때의 정보를 담아둔 것
	GetObject(m_hLoadBitmap, sizeof(BITMAP), &m_BitmapInfo);



	// 읽기 
	BinaryReadStream BinaryRead = BinaryReadStream(_Path);

	// fseek라는 함수를 이용, 알파값
	BinaryRead.Binary_Seek(sizeof(BITMAPFILEHEADER));
	BinaryRead.Binary_Read(&m_AlphaBitmapInfo, sizeof(m_AlphaBitmapInfo), sizeof(m_AlphaBitmapInfo));

	// 32비트 이상부터 알파값 변경가능
	if (32 <= m_AlphaBitmapInfo.biBitCount)
	{
		m_bAlpha = true;
	}


	return true;
}
