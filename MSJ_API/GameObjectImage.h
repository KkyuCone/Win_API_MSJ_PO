#pragma once

class ResourceManager;
class GameObjectSprite;
class GameObjectImage
{
public:
	friend ResourceManager;

private:
	// 이미지가 가진 픽셀정보등을 가지고 있고.
	// 윈도우에서 얻어온 hdc도 사실 똑같이 가지고 있다. 
	HDC m_ImageDC;

	// 비트맵 자체에 대한 핸들
	HBITMAP m_hLoadBitmap;
	HBITMAP m_hObjBitmap;

	BITMAP m_BitmapInfo;

	BITMAPINFOHEADER m_AlphaBitmapInfo;

	// 투명처리할 때 사용할 컬러
	UINT m_TransColor;

	// 반투명이 가능한 이미지인지 확인할 변수
	bool m_bAlpha;


public:
	bool Alpha_Value()
	{
		return m_bAlpha;
	}


	HDC ObjectImageDC()
	{
		return m_ImageDC;
	}

	UINT Width()
	{
		return m_BitmapInfo.bmWidth;
	}

	UINT Height()
	{
		return m_BitmapInfo.bmHeight;
	}

	UINT TransColor()
	{
		return m_TransColor;
	}

	COLORREF GetPixelColor(int _X, int _Y);
	void SetPixelColor(int _X, int _Y, COLORREF _Color);

	// void TransDraw(int _X, int _Y, GameObjectSprite* _p);  <- 웜즈 같은 ..땅팠을때 그림 새로그리기

private:
	void TransColor(UINT _Color)
	{
		m_TransColor = _Color;
	}


public:
	bool Create_EmptyImage(F_Size _Size);		// 빈 이미지를 만들 수 있는 함수
	bool Resource_Load(const wchar_t* _Path);


private:
	GameObjectImage();
	~GameObjectImage();
};

