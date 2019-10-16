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

// �� �̹���
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

	// �̹��� �ε�
	m_hLoadBitmap = (HBITMAP)LoadImageW(Util_Core::Instance().WINDOW_INSTANCE(), _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	Tassert(nullptr == Util_Core::Instance().WINDOW_INSTANCE());

	// �̹����� ��ã�Ҵٸ�(�ش� ��ο� �̹����� ���ٸ�)
	if (nullptr == m_hLoadBitmap)
	{
		return false;
	}

	// �ε�� �ڵ��� ���� ������ ������ �� �� �ִ� HDC�� ��������.
	// ������ DC�� ������ �� �� �ִ� DC�� ����� ����.
	// ��������� ���� ���ο� 1*1 ��Ʈ�� �̹����� ���������.
	m_ImageDC = CreateCompatibleDC(Util_Core::Instance().WINDOW_DC());
	Tassert(nullptr == m_ImageDC);

	// ���ο� �ִ� 1*1 �̹����� ���� �ε��� �̹����� ��ü
	m_hObjBitmap = (HBITMAP)SelectObject(m_ImageDC, m_hLoadBitmap);

	// �� �Լ��� �̹��������� ������ �����°��� �ƴ϶� �ε�Ǿ� ���� �ö��� ���� ������ ��Ƶ� ��
	GetObject(m_hLoadBitmap, sizeof(BITMAP), &m_BitmapInfo);



	// �б� 
	BinaryReadStream BinaryRead = BinaryReadStream(_Path);

	// fseek��� �Լ��� �̿�, ���İ�
	BinaryRead.Binary_Seek(sizeof(BITMAPFILEHEADER));
	BinaryRead.Binary_Read(&m_AlphaBitmapInfo, sizeof(m_AlphaBitmapInfo), sizeof(m_AlphaBitmapInfo));

	// 32��Ʈ �̻���� ���İ� ���氡��
	if (32 <= m_AlphaBitmapInfo.biBitCount)
	{
		m_bAlpha = true;
	}


	return true;
}
