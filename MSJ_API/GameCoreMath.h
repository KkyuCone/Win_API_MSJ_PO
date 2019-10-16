#pragma once
#include "Render_Vector.h"
#include <math.h>


class GameCoreMath
{
public:
	static const float Pi;		// ����
	static const float DegTransRad;		// �������� ��ȯ (ȣ����)
	static const float RadTransDeg;		// ������ ��ȯ

public:
	//  _Degree(����)��ŭ ȸ���� x,y��
	static F_Position DegreeRotPos(float _Degree)
	{
		float Rad = _Degree * DegTransRad;
		return{ cosf(Rad), -sinf(Rad) };	
	}

	// �غ� ���ϱ�(�� Left�� Right�� �Ÿ�)
	static float LowerBase(const F_Position& _Left, const F_Position& _Right)
	{
		float Distance = _Left.X - _Right.X;

		//if (Distance < 0)
		//{
		//	Distance *= -1.0f;
		//}

		return Distance;
	}

	// ���� ���ϱ�
	static float Height(const F_Position& _Left, const F_Position& _Right) 
	{
		float Distance = _Left.Y - _Right.Y;

		//if (Distance < 0)
		//{
		//	Distance *= -1.0f;
		//}

		return Distance;
	}

	// ���� ���ϱ�
	static float Hypotenuse(const F_Position& _Left, const F_Position& _Right)
	{
		float lowerBase = LowerBase(_Left, _Right);
		float height = Height(_Left, _Right);

		// ��Ÿ��� ���� �̿� a^2 + b^2 = c^2
		// sqrtf -> ��Ʈ, ������
		return sqrtf(lowerBase * lowerBase + height * height);
	}

	// ���� �޸��� Ȯ��

	// ���� (���Ȱ�)
	static float PtoP_Radian(const F_Position& _Left, const F_Position& _Right)
	{
		float lowerBase = LowerBase(_Left, _Right);
		float height = Height(_Left, _Right) * -1.0f;
		float hypotenuse = Hypotenuse(_Left, _Right);

		// ��ũź��Ʈ�� ���ϱ�
		float ATangent = atan2(height, lowerBase);
		return ATangent;

		// �ڻ���, Y,X��ǥ�� ���ϱ�
		//float Cosine = lowerBase / hypotenuse;
		//float Rad = acosf(Cosine);
		//return Rad;
	}

	// �����˾Ƴ���
	static float PtoP_Degree(const F_Position& _Left, const F_Position& _Right)
	{

		float Rad = PtoP_Radian(_Left, _Right) *  RadTransDeg;

		// ź��Ʈ
		Rad = 180.0f + Rad;

		// X, Y��ǥ�� ���� ��� (�غ�,���� �Ѵ� ���밪 �ּ�Ǯ��)

		//float PosLX = _Left.X;
		//float PosRX = _Right.X;
		//float PosLY = _Left.Y;
		//float PosRY = _Right.Y;
		//if ((PosLX - PosRX) < 0 && (PosLY - PosRY) >= 0)		// 1��и�
		//{
		//}
		//else  if ((PosLX - PosRX) >= 0 && (PosLY - PosRY) > 0)	// 2��и�
		//{
		//	Rad = 90.0f + (90.0f - Rad);
		//}
		//else if ((PosLX - PosRX) > 0 && (PosLY - PosRY) <= 0)	// 3��и�
		//{
		//	Rad = 180.0f + Rad;
		//}
		//else if ((PosLX - PosRX) <= 0 && (PosLY - PosRY) < 0)	// 4��и�
		//{
		//	Rad = 270.0f + (90.0f - Rad);
		//}

		return Rad;
	}


	// �浹����
	// ���簢 - ���簢
	static bool RECT_RECT(const F_Rectangle& _Left, const F_Rectangle& _Right)
	{
		if (_Left.FLeft() > _Right.FRight())
		{
			return false;
		}

		if (_Left.FRight() < _Right.FLeft())
		{
			return false;
		}

		if (_Left.FTop() > _Right.FBottom())
		{
			return false;
		}

		if (_Left.FBottom() < _Right.FTop())
		{
			return false;
		}

		return true;
	}

	
	// ���簢 - ��
	static bool RECT_CIRCLE(const F_Rectangle& _Left, const F_Rectangle& _Right)
	{
		F_Rectangle HeightR = _Left;
		F_Rectangle WidthR = _Left;

		HeightR.Size.Y = _Right.Size.X;
		WidthR.Size.X = _Right.Size.X;

		if (true == RECT_POINT(HeightR, _Right.Position)
			|| true == RECT_POINT(WidthR, _Right.Position) )
		{
			return true;
		}

		if (true == CIRCLE_POINT(_Right, _Left.F_LeftTop()) ||
			true == CIRCLE_POINT(_Right, _Left.F_RightTop()) ||
			true == CIRCLE_POINT(_Right, _Left.F_LeftBottom()) ||
			true == CIRCLE_POINT(_Right, _Left.F_RightBottom()))
		{
			return true;
		}

		return false;
	}

	// ���簢 - ��
	static bool RECT_POINT(const F_Rectangle& _Left, const F_Position& _Right)
	{

		if (_Left.FLeft() > _Right.X)
		{
			return false;
		}

		if (_Left.FRight() < _Right.X)
		{
			return false;
		}

		if (_Left.FTop() > _Right.Y)
		{
			return false;
		}

		if (_Left.FBottom() < _Right.Y)
		{
			return false;
		}

		return true;
	}

	// �� - ��
	static bool CIRCLE_CIRCLE(const F_Rectangle& _Left, const F_Rectangle& _Right)
	{
		float Distance = Hypotenuse(_Left.Position, _Right.Position);

		if (_Left.Size.Half_FloatX() + _Right.Size.Half_FloatY() > Distance)
		{
			return true;
		}

		return false;
	}


	// �� - ��
	static bool CIRCLE_POINT(const F_Rectangle& _Left, const F_Position& _Right)
	{
		float Distance = Hypotenuse(_Left.Position, _Right);

		if (_Left.Size.Half_FloatX() > Distance)
		{
			return true;
		}

		return false;
	}

	// �� - ��
	static bool POINT_POINT(const F_Rectangle& _Left, const F_Rectangle& _Right)
	{
		return _Left.Position == _Right.Position;
	}


		
public:
	GameCoreMath();
	~GameCoreMath();
};

