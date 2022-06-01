#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;	
	static const float DegreeToRadian;	//60분법->호도법(0.017453...)
	static const float RadianToDegree;	//호도법->60분법(57.29577...)
};

class float4
{
public:
	//자주 사용하는 숫자 조합을 미리 만들어놓으면 생성자 호출하는 연산비용을 아낄 수 있다.

	static const float4 Zero;
	static const float4 One;

	static const float4 Left;	//--x
	static const float4 Right;	//++x
	static const float4 Down;		//++y
	static const float4 Up;	//--y

	static const float4 Red;	//100
	static const float4 Green;	//010
	static const float4 Blue;	//001
	static const float4 Yellow;	//110
	static const float4 Magenta;//101
	static const float4 Cyan;	//001

	static const float4 Black;	//000
	static const float4 White;	//111

	//익명으로 유니온을 선언하고 그 안에 구조체를 두면, 
	//유니온처럼 메모리를 공용으로 활용할 수 있는 클래스 멤버 구조체를 사용할 수 있다.
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
		float4 result;
		result.x = this->x + _other.x;
		result.y = this->y + _other.y;
		result.z = this->z + _other.z;
		result.w = this->w + _other.w;

		return result;
	}

	float4 operator-(const float4& _other) const
	{
		float4 result;
		result.x = this->x - _other.x;
		result.y = this->y - _other.y;
		result.z = this->z - _other.z;
		result.w = this->w - _other.w;

		return result;
	}

	float4 operator*(const float4& _other) const
	{
		float4 result;
		result.x = this->x * _other.x;
		result.y = this->y * _other.y;
		result.z = this->z * _other.z;
		result.w = this->w * _other.w;

		return result;
	}

	float4 operator/(const float4& _other) const
	{
		float4 result;
		result.x = this->x / _other.x;
		result.y = this->y / _other.y;
		result.z = this->z / _other.z;
		result.w = this->w / _other.w;

		return result;
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
		float4 result;
		result.x = this->x * _value;
		result.y = this->y * _value;
		result.z = this->z * _value;
		result.w = this->w * _value;

		return result;
	}
	float4 operator/(const float _value) const
	{
		float4 result;
		result.x = this->x / _value;
		result.y = this->y / _value;
		result.z = this->z / _value;
		result.w = this->w / _value;

		return result;
	}
	const float4& operator*=(const float _value)
	{
		this->x = this->x * _value;
		this->y = this->y * _value;
		this->z = this->z * _value;
		this->w = this->w * _value;

		return *this;
	}
	const float4& operator/=(const float _value)
	{
		this->x = this->x / _value;
		this->y = this->y / _value;
		this->z = this->z / _value;
		this->w = this->w / _value;

		return *this;
	}

	bool operator==(const float4& _value) const
	{
		return (this->x == _value.x && this->y == _value.y && this->z == _value.z);
	}

	bool operator!=(const float4& _value) const
	{
		return (this->x != _value.x || this->y != _value.y || this->z != _value.z);
	}


public:
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

	int Half_IntX() const 
	{
		return static_cast<int>(x * 0.5f);
	}

	int Half_IntY() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int Half_IntZ() const
	{
		return static_cast<int>(z * 0.5f);
	}

public:
	static float4 Cal2DRotationByDegree(const float4& _originVector, float _degree)
	{
		return Cal2DRotationByRadian(_originVector, _degree * GameEngineMath::DegreeToRadian);
	}

	static float4 Cal2DRotationByRadian(const float4& _originVector, float _radian)
	{
		float4 result;

		result.x = _originVector.x * cosf(_radian) - _originVector.y * sinf(_radian);
		result.y = _originVector.x * sinf(_radian) + _originVector.y * cosf(_radian);

		return result;
	}

	void Rotate2DByDegree(float _degree)
	{
		(*this) = float4::Cal2DRotationByDegree(*this, _degree);
	}

	void Rotate2DByRadian(float _radian)
	{
		(*this) = float4::Cal2DRotationByRadian(*this, _radian);
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
