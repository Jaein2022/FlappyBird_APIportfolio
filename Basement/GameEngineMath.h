#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float TAU;	
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

		struct
		{
			float r;
			float g;
			float b;
			float a;
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


	const float4& operator=(const float4& _other)
	{
		this->x = _other.x;
		this->y = _other.y;
		this->z = _other.z;
		this->w = _other.w;
		return *this;
	}

	float4 operator+(const float4& _other) const
	{
		float4 returnValue;
		returnValue.x = this->x + _other.x;
		returnValue.y = this->y + _other.y;
		returnValue.z = this->z + _other.z;
		returnValue.w = this->w + _other.w;

		return returnValue;
	}

	float4 operator-(const float4& _other) const
	{
		float4 returnValue;
		returnValue.x = this->x - _other.x;
		returnValue.y = this->y - _other.y;
		returnValue.z = this->z - _other.z;
		returnValue.w = this->w - _other.w;

		return returnValue;
	}

	float4 operator*(const float4& _other) const
	{
		float4 returnValue;
		returnValue.x = this->x * _other.x;
		returnValue.y = this->y * _other.y;
		returnValue.z = this->z * _other.z;
		returnValue.w = this->w * _other.w;

		return returnValue;
	}

	float4 operator/(const float4& _other) const
	{
		float4 returnValue;
		returnValue.x = this->x / _other.x;
		returnValue.y = this->y / _other.y;
		returnValue.z = this->z / _other.z;
		returnValue.w = this->w / _other.w;

		return returnValue;
	}

	const float4& operator+=(const float4& _other)
	{
		this->x = this->x + _other.x;
		this->y = this->y + _other.y;
		this->z = this->z + _other.z;
		this->w = this->w + _other.w;

		return *this;
	}

	const float4& operator-=(const float4& _other)
	{
		this->x = this->x - _other.x;
		this->y = this->y - _other.y;
		this->z = this->z - _other.z;
		this->w = this->w - _other.w;

		return *this;
	}

	const float4& operator*=(const float4& _other)
	{
		this->x = this->x * _other.x;
		this->y = this->y * _other.y;
		this->z = this->z * _other.z;
		this->w = this->w * _other.w;

		return *this;
	}

	const float4& operator/=(const float4& _other)
	{
		this->x = this->x / _other.x;
		this->y = this->y / _other.y;
		this->z = this->z / _other.z;
		this->w = this->w / _other.w;

		return *this;
	}

	float4 operator*(const float _value) const
	{
		float4 returnValue;
		returnValue.x = this->x * _value;
		returnValue.y = this->y * _value;
		returnValue.z = this->z * _value;
		returnValue.w = this->w * _value;

		return returnValue;
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

public:
	static float4 RotateByDegree(float4 _originVector, float _degree)
	{
		return RotateByRadian(_originVector, _degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateByRadian(float4 _originVector, float _radian)
	{
		float4 nextVector;

		nextVector.x = _originVector.x * cosf(_radian) - _originVector.y * sinf(_radian);
		nextVector.y = _originVector.x * sinf(_radian) + _originVector.y * cosf(_radian);

		return nextVector;
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



};

struct GameEngineRect
{

	float4 pos_;
	float4 size_;

public:
	GameEngineRect(const float4& _pos, const float4& _size): pos_(_pos), size_(_size)
	{
	}

	~GameEngineRect()
	{
	}

public:
	float Left()
	{
		return pos_.x - size_.Half_X();
	}	
	float Right()
	{
		return pos_.x + size_.Half_X();
	}	
	float Top()
	{
		return pos_.y - size_.Half_Y();
	}	
	float Bot()
	{
		return pos_.y - size_.Half_Y();
	}

	int ILeft()
	{
		return pos_.IntX() - size_.Half_IntX();
	}	
	int IRight()
	{
		return pos_.IntX() + size_.Half_IntX();
	}	
	int ITop()
	{
		return pos_.IntY() - size_.Half_IntY();
	}	
	int IBot()
	{
		return pos_.IntY() + size_.Half_IntY();
	}

	float4 LeftTopfloat4()
	{
		return { Left(), Top() };
	}
	float4 RightTopfloat4()
	{
		return { Right(), Top() };
	}
	float4 LeftBotfloat4()
	{
		return { Left(), Bot() };
	}
	float4 RightBotfloat4()
	{
		return { Right(), Bot() };
	}

private:

};
