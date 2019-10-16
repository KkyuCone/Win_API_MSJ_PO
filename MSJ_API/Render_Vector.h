#pragma once

class VECTOR2
{
public:
	static const VECTOR2 LEFT;
	static const VECTOR2 RIGHT;
	static const VECTOR2 UP;
	static const VECTOR2 DOWN;
	static const VECTOR2 ONE;		// (1, 1)
	static const VECTOR2 ZERO;		// (0, 0)

public:
	float X;
	float Y;

public:
	// ������
	VECTOR2() : X(0.0f), Y(0.0f) {}
	VECTOR2(float _X, float _Y) : X(_X), Y(_Y) {}
	VECTOR2(int _X, int _Y) : X((float)_X), Y((float)_Y) {}
	VECTOR2(int _X, float _Y) : X((float)_X), Y(_Y) {}
	VECTOR2(float _X, int _Y) : X(_X), Y((float)_Y) {}
	VECTOR2(unsigned int _X, unsigned int _Y) : X((float)_X), Y((float)_Y) {}

public:
	int IntX() const { return (int)X; }
	int IntY() const { return (int)Y; }

	// �� ����
	int Half_IntX() const { return (int)(X * 0.5f); }
	int Half_IntY() const { return (int)(Y * 0.5f); }

	float Half_FloatX() const { return X * 0.5f; }
	float Half_FloatY() const { return Y * 0.5f; }

public:
	VECTOR2 Half_VECTOR2() { return{ Half_IntX(),  Half_IntY() }; }

	VECTOR2 operator+(const VECTOR2& _Other) const
	{
		return{ X + _Other.X, Y + _Other.Y };
	}

	VECTOR2 operator+=(const VECTOR2& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;

		return *this;
	}

	bool operator==(const VECTOR2& _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	VECTOR2 operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;

		return *this;
	}

	VECTOR2 operator-=(const VECTOR2& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;

		return *this;
	}

	VECTOR2 operator-(const VECTOR2& _Other) const
	{
		return{ X - _Other.X, Y - _Other.Y };
	}

	VECTOR2 operator*(const float _Value) const
	{
		return{ X * _Value, Y *_Value };
	}
};

typedef VECTOR2 F_Position;
typedef VECTOR2 F_Size;

class VECTOR2_INT
{
public:
	// ����ӵ�
	union
	{
		__int64 Value;
		struct
		{
			int X;
			int Y;
		};
	};

public:
	// ����ȯ �����ε�
	operator __int64()
	{
		// __int64 Key;
		// memcpy_s(&Key, sizeof(__int64), this, sizeof(__int64));
		return Value;
	}



	VECTOR2_INT& operator-= (const F_Position& _Value)
	{
		X -= (int)_Value.X;
		Y -= (int)_Value.Y;

		return *this;
	}

	VECTOR2_INT& operator+ (const VECTOR2_INT& _Value)
	{
		X += (int)_Value.X;
		Y += (int)_Value.Y;

		return *this;
	}

	VECTOR2_INT& operator+= (const F_Position& _Value)
	{
		X += (int)_Value.X;
		Y += (int)_Value.Y;

		return *this;
	}

	VECTOR2_INT& operator= (const F_Position& _Value)
	{
		X = (int)_Value.X;
		Y = (int)_Value.Y;

		return *this;
	}

public:
	VECTOR2_INT() : X(0), Y(0)
	{

	}

	VECTOR2_INT(__int64 _Value) : Value(_Value)
	{

	}

	VECTOR2_INT(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

};

typedef VECTOR2_INT I_Position;
typedef VECTOR2_INT I_Size;


// ���� �̰��� ������ �����Ѵٸ� size.x�� ������ �ش��Ѵ�. 
class F_Rectangle
{
public:
	F_Position Position;
	F_Size Size;

public:
	F_Rectangle() : Position(), Size() {}
	F_Rectangle(F_Position _pos, F_Size _size) : Position(_pos), Size(_size) {}

public:
	// �ڷ��� float
	float FLeft()					const { return Position.X - Size.Half_FloatX(); }
	float FRight()					const { return Position.X + Size.Half_FloatX(); }
	float FTop()					const { return Position.Y - Size.Half_FloatY(); }
	float FBottom()				const { return Position.Y + Size.Half_FloatY(); }

	F_Position F_Left()		const { return{ FLeft(), Position.Y }; }
	F_Position F_Right()		const { return{ FRight(), Position.Y }; }
	F_Position F_Top()			const { return{ Position.X, FTop() }; }
	F_Position F_Bottom()		const { return{ Position.X, FBottom() }; }

	F_Position F_LeftTop()		const { return{ FLeft(), FTop() }; }			// ���� ���� ����
	F_Position F_RightTop()	const { return{ FRight(), FTop() }; }
	F_Position F_LeftBottom()	const { return{ FLeft(), FBottom() }; }
	F_Position F_RightBottom()	const { return{ FRight(), FBottom() }; }


	// �ڷ��� int
	int I_Left() { return (int)FLeft(); }
	int I_Right() { return (int)FRight(); }
	int I_Top() { return (int)FTop(); }
	int I_Botton() { return (int)FBottom(); }

	I_Position I_Move_Left() { return{ I_Left(), Position.IntY() }; }
	I_Position I_Move_Right() { return{ I_Right(), Position.IntY() }; }
	I_Position I_Move_Top() { return{ Position.IntX(), I_Top() }; }
	I_Position I_Mvoe_Bottom() { return{ Position.IntX(), I_Botton() }; }

	I_Position I_Move_LeftTop()		 { return{ I_Left(), I_Top() }; }			// ���� ���� ����
	I_Position I_Move_RightTop()	 { return{ I_Right(), I_Top() }; }
	I_Position I_Move_LeftBottom()	 { return{ I_Left(), I_Botton() }; }
	I_Position I_Move_RightBottom()	 { return{ I_Right(), I_Botton() }; }

};
