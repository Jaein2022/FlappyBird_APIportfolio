#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float TAU;	//Tau
	static const float DegreeToRadian;	//60�й�->ȣ����(0.017453...)
	static const float RadianToDegree;	//ȣ����->60�й�(57.29577...)
};

class float4
{
public:
	//���� ����ϴ� ���� ������ �̸� ���������� ������ ȣ���ϴ� �������� �Ƴ� �� �ִ�.
	static const float4 ZERO;
	static const float4 ONE;
	static const float4 LEFT;	//--x
	static const float4 RIGHT;	//++x
	static const float4 UP;		//++y
	static const float4 DOWN;	//--y

	static const float4 RED;
	static const float4 GREEN;
	static const float4 BLUE;
	static const float4 BLACK;
	static const float4 WHITE;
	static const float4 NONE;

public:
	static float4 RotateByDegree(float4 _originVector, float _degree)
	{
		return RotateByRadian(_originVector, _degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateByRadian(float4 _originVector, float _radian)
	{
		float4 NextVector;

		NextVector.x = _originVector.x * cosf(_radian) - _originVector.y * sinf(_radian);
		NextVector.y = _originVector.x * sinf(_radian) + _originVector.y * cosf(_radian);

		return NextVector;
	}

	static float4 ConvertToDegree(float _degree)
	{
		return ConvertToRadian(_degree * GameEngineMath::DegreeToRadian);
	}
	static float4 ConvertToRadian(float _radian)		//���Ͱ� 0���϶� ���͸� ȸ����Ű�� ����.
	{
		return float4(cosf(_radian), sinf(_radian));
	}
	static float4 ConvertToRadian(float4 vector, float _radian)
	{
		return float4(cosf(_radian), sinf(_radian));
	}

public:
	//�͸����� ���Ͽ��� �����ϰ� �� �ȿ� ����ü�� �θ�, 
	//���Ͽ�ó�� �޸𸮸� �������� Ȱ���� �� �ִ� Ŭ���� ��� ����ü�� ����� �� �ִ�.
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;	
		};
	};

	float4() : x(0.f), y(0.f), z(0.f), w(1.f)
	{
	}

	float4(const float4& _other) : x(_other.x), y(_other.y), z(_other.z), w(_other.w)
	{
	}

	float4(float4&& _value) noexcept : x(_value.x), y(_value.y), z(_value.z), w(_value.w)
	{
	}

	float4(int _x, int _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(0.f), w(1.f)
	{
	}

	float4(float _x, float _y) : x(_x), y(_y), z(0.f), w(1.f)
	{
	}

	float4(int _x, int _y, int _z)
		: x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(1.0f)
	{
	}

	float4(float _x, float _y, float _z, float _w = 1.f) : x(_x), y(_y), z(_z), w(_w)
	{
	}

	~float4()
	{
	}


	float4& operator=(const float4& _other)
	{
		this->x = _other.x;
		this->y = _other.y;
		this->z = _other.z;
		this->w = _other.w;
		return *this;
	}

	float4 operator+(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x = this->x + _other.x;
		ReturnValue.y = this->y + _other.y;
		ReturnValue.z = this->z + _other.z;
		ReturnValue.w = this->w + _other.w;

		return ReturnValue;
	}

	float4 operator-(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x = this->x - _other.x;
		ReturnValue.y = this->y - _other.y;
		ReturnValue.z = this->z - _other.z;
		ReturnValue.w = this->w - _other.w;

		return ReturnValue;
	}

	float4 operator*(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x = this->x * _other.x;
		ReturnValue.y = this->y * _other.y;
		ReturnValue.z = this->z * _other.z;
		ReturnValue.w = this->w * _other.w;

		return ReturnValue;
	}

	float4 operator/(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x = this->x / _other.x;
		ReturnValue.y = this->y / _other.y;
		ReturnValue.z = this->z / _other.z;
		ReturnValue.w = this->w / _other.w;

		return ReturnValue;
	}

	float4& operator+=(const float4 _other)
	{
		this->x = this->x + _other.x;
		this->y = this->y + _other.y;
		this->z = this->z + _other.z;
		this->w = this->w + _other.w;

		return *this;
	}

	float4& operator-=(const float4 _other)
	{
		this->x = this->x - _other.x;
		this->y = this->y - _other.y;
		this->z = this->z - _other.z;
		this->w = this->w - _other.w;

		return *this;
	}

	float4& operator*=(const float4 _other)
	{
		this->x = this->x * _other.x;
		this->y = this->y * _other.y;
		this->z = this->z * _other.z;
		this->w = this->w * _other.w;

		return *this;
	}

	float4& operator/=(const float4 _other)
	{
		this->x = this->x / _other.x;
		this->y = this->y / _other.y;
		this->z = this->z / _other.z;
		this->w = this->w / _other.w;

		return *this;
	}

	float4 operator*(const float _value) const
	{
		float4 ReturnValue;
		ReturnValue.x = this->x * _value;
		ReturnValue.y = this->y * _value;
		ReturnValue.z = this->z * _value;
		ReturnValue.w = this->w * _value;

		return ReturnValue;
	}

	//x, y�� ��.
	bool operator==(const float4& _value) const	
	{
		return (this->x == _value.x && this->y == _value.y);
	}

	//x, y�� ��.
	bool operator!=(const float4& _value) const	
	{
		return (this->x != _value.x || this->y != _value.y);
	}

	float Half_X()
	{
		return x * 0.5f;
	}

	float Half_Y()
	{
		return y * 0.5f;
	}

	float Half_Z()
	{
		return z * 0.5f;
	}

	float4 Half()
	{
		return { Half_X(), Half_Y(), Half_Z() };
	}

	int IntX() const
	{
		return static_cast<int>(x);
	}

	int IntY() const
	{
		return static_cast<int>(y);
	}

	int IntZ() const
	{
		return static_cast<int>(z);
	}

	int Half_IntX()
	{
		return static_cast<int>(x * 0.5f);
	}

	int Half_IntY()
	{
		return static_cast<int>(y * 0.5f);
	}

	int Half_IntZ()
	{
		return static_cast<int>(z * 0.5f);
	}

};