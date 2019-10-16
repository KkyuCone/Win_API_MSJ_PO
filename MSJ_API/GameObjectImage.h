#pragma once

class ResourceManager;
class GameObjectSprite;
class GameObjectImage
{
public:
	friend ResourceManager;

private:
	// �̹����� ���� �ȼ��������� ������ �ְ�.
	// �����쿡�� ���� hdc�� ��� �Ȱ��� ������ �ִ�. 
	HDC m_ImageDC;

	// ��Ʈ�� ��ü�� ���� �ڵ�
	HBITMAP m_hLoadBitmap;
	HBITMAP m_hObjBitmap;

	BITMAP m_BitmapInfo;

	BITMAPINFOHEADER m_AlphaBitmapInfo;

	// ����ó���� �� ����� �÷�
	UINT m_TransColor;

	// �������� ������ �̹������� Ȯ���� ����
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

	// void TransDraw(int _X, int _Y, GameObjectSprite* _p);  <- ���� ���� ..�������� �׸� ���α׸���

private:
	void TransColor(UINT _Color)
	{
		m_TransColor = _Color;
	}


public:
	bool Create_EmptyImage(F_Size _Size);		// �� �̹����� ���� �� �ִ� �Լ�
	bool Resource_Load(const wchar_t* _Path);


private:
	GameObjectImage();
	~GameObjectImage();
};

