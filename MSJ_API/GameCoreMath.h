#pragma once
#include "Render_Vector.h"
#include <math.h>


class GameCoreMath
{
public:
	static const float Pi;		// 파이
	static const float DegTransRad;		// 라디안으로 변환 (호도법)
	static const float RadTransDeg;		// 각도로 변환

public:
	//  _Degree(각도)만큼 회전한 x,y값
	static F_Position DegreeRotPos(float _Degree)
	{
		float Rad = _Degree * DegTransRad;
		return{ cosf(Rad), -sinf(Rad) };	
	}

	// 밑변 구하기(점 Left와 Right의 거리)
	static float LowerBase(const F_Position& _Left, const F_Position& _Right)
	{
		float Distance = _Left.X - _Right.X;

		//if (Distance < 0)
		//{
		//	Distance *= -1.0f;
		//}

		return Distance;
	}

	// 높이 구하기
	static float Height(const F_Position& _Left, const F_Position& _Right) 
	{
		float Distance = _Left.Y - _Right.Y;

		//if (Distance < 0)
		//{
		//	Distance *= -1.0f;
		//}

		return Distance;
	}

	// 빗변 구하기
	static float Hypotenuse(const F_Position& _Left, const F_Position& _Right)
	{
		float lowerBase = LowerBase(_Left, _Right);
		float height = Height(_Left, _Right);

		// 피타고라스 정리 이용 a^2 + b^2 = c^2
		// sqrtf -> 루트, 제곱근
		return sqrtf(lowerBase * lowerBase + height * height);
	}

	// 숙제 메모장 확인

	// 각도 (라디안값)
	static float PtoP_Radian(const F_Position& _Left, const F_Position& _Right)
	{
		float lowerBase = LowerBase(_Left, _Right);
		float height = Height(_Left, _Right) * -1.0f;
		float hypotenuse = Hypotenuse(_Left, _Right);

		// 아크탄젠트로 구하기
		float ATangent = atan2(height, lowerBase);
		return ATangent;

		// 코사인, Y,X좌표로 구하기
		//float Cosine = lowerBase / hypotenuse;
		//float Rad = acosf(Cosine);
		//return Rad;
	}

	// 각도알아내기
	static float PtoP_Degree(const F_Position& _Left, const F_Position& _Right)
	{

		float Rad = PtoP_Radian(_Left, _Right) *  RadTransDeg;

		// 탄젠트
		Rad = 180.0f + Rad;

		// X, Y좌표로 각도 재기 (밑변,높이 둘다 절대값 주석풀기)

		//float PosLX = _Left.X;
		//float PosRX = _Right.X;
		//float PosLY = _Left.Y;
		//float PosRY = _Right.Y;
		//if ((PosLX - PosRX) < 0 && (PosLY - PosRY) >= 0)		// 1사분면
		//{
		//}
		//else  if ((PosLX - PosRX) >= 0 && (PosLY - PosRY) > 0)	// 2사분면
		//{
		//	Rad = 90.0f + (90.0f - Rad);
		//}
		//else if ((PosLX - PosRX) > 0 && (PosLY - PosRY) <= 0)	// 3사분면
		//{
		//	Rad = 180.0f + Rad;
		//}
		//else if ((PosLX - PosRX) <= 0 && (PosLY - PosRY) < 0)	// 4사분면
		//{
		//	Rad = 270.0f + (90.0f - Rad);
		//}

		return Rad;
	}


	// 충돌관련
	// 직사각 - 직사각
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

	
	// 직사각 - 원
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

	// 직사각 - 점
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

	// 원 - 원
	static bool CIRCLE_CIRCLE(const F_Rectangle& _Left, const F_Rectangle& _Right)
	{
		float Distance = Hypotenuse(_Left.Position, _Right.Position);

		if (_Left.Size.Half_FloatX() + _Right.Size.Half_FloatY() > Distance)
		{
			return true;
		}

		return false;
	}


	// 원 - 점
	static bool CIRCLE_POINT(const F_Rectangle& _Left, const F_Position& _Right)
	{
		float Distance = Hypotenuse(_Left.Position, _Right);

		if (_Left.Size.Half_FloatX() > Distance)
		{
			return true;
		}

		return false;
	}

	// 점 - 점
	static bool POINT_POINT(const F_Rectangle& _Left, const F_Rectangle& _Right)
	{
		return _Left.Position == _Right.Position;
	}


		
public:
	GameCoreMath();
	~GameCoreMath();
};

