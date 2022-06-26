#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;	
	static const float DegreeToRadian;	//60�й�->ȣ����(0.017453...)
	static const float RadianToDegree;	//ȣ����->60�й�(57.29577...)
};

class float4
{
public:
	//���� ����ϴ� ���� ������ �̸� ���������� ������ ȣ���ϴ� �������� �Ƴ� �� �ִ�.

	static const float4 Zero;	//0000
	static const float4 One;	//1111

	static const float4 Left;	//--x
	static const float4 Right;	//++x
	static const float4 Down;	//++y
	static const float4 Up;		//--y

	static const float4 Red;	//1001
	static const float4 Green;	//0101
	static const float4 Blue;	//0011
	static const float4 Yellow;	//1101
	static const float4 Magenta;//1011
	static const float4 Cyan;	//0011

	static const float4 Black;	//0001
	static const float4 White;	//1111

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

	bool operator==(const float4& _other) const
	{
		return fabsf(this->x - _other.x) <= FLT_EPSILON &&
			fabsf(this->y - _other.y) <= FLT_EPSILON &&
			fabsf(this->z - _other.z) <= FLT_EPSILON;
		//FLT_EPSILON: 1.192092896e-07F. float���� ǥ���� �� �ִ� ���� ���� �� + 1.0f.
		//�Ǽ��� �ε��Ҽ��� �ý��� ������ �׻� �ణ�� ������ �߻��ϰ�, �׷��� �Ϲ����� ������� ��Ҹ� ���ؼ� �ȵǰ�,
		//�� ���ڰ� ���̰� ������ �Ǵ� ���� ��ġ ������ �� ���ٰ� ǥ���ϰ�, �׺��� ũ�ٸ� �ٸ��ٰ� ǥ���ϴ� ����� ��� �Ѵ�.
	}

	bool operator!=(const float4& _other) const
	{
		return fabsf(this->x - _other.x) > FLT_EPSILON ||
			fabsf(this->y - _other.y) > FLT_EPSILON ||
			fabsf(this->z - _other.z) > FLT_EPSILON;
		//FLT_EPSILON: 1.192092896e-07F. float���� ǥ���� �� �ִ� ���� ���� �� + 1.0f.
		//�Ǽ��� �ε��Ҽ��� �ý��� ������ �׻� �ణ�� ������ �߻��ϰ�, �׷��� �Ϲ����� ������� ��Ҹ� ���ؼ� �ȵǰ�,
		//�� ���ڰ� ���̰� ������ �Ǵ� ���� ��ġ ������ �� ���ٰ� ǥ���ϰ�, �׺��� ũ�ٸ� �ٸ��ٰ� ǥ���ϴ� ����� ��� �Ѵ�.
	}


public:
	float Half_X() const
	{
		return x * 0.5f;
	}

	float Half_Y() const
	{
		return y * 0.5f;
	}

	float Half_Z() const
	{
		return z * 0.5f;
	}

	float4 Half() const
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

	const float4& Rotate2DByDegree(float _degree)
	{
		(*this) = float4::Cal2DRotationByDegree(*this, _degree);
		return *this;
	}

	const float4& Rotate2DByRadian(float _radian)
	{
		(*this) = float4::Cal2DRotationByRadian(*this, _radian);
		return *this;
	}

	POINT ConvertToPoint()
	{
		return POINT{ this->IntX(), this->IntY() };
	}
};

struct GameEngineRect
{
	float4 pos_;
	float4 size_;

	float4 leftTop_;
	float4 leftBot_;
	float4 rightTop_;
	float4 rightBot_;

public:
	GameEngineRect(const float4& _pos, const float4& _size): pos_(_pos), size_(_size)
	{
		leftTop_ = { pos_.x - size_.Half_X(), pos_.y - size_.Half_Y() };
		leftBot_ = { pos_.x - size_.Half_X(), pos_.y + size_.Half_Y() };
		rightTop_ = { pos_.x + size_.Half_X(), pos_.y - size_.Half_Y() };
		rightBot_ = { pos_.x + size_.Half_X(), pos_.y + size_.Half_Y() };
	}

	~GameEngineRect()
	{
	}

public:
	float Left()
	{
		return leftTop_.x;
	}	
	float Right()
	{
		return rightTop_.x;
	}	
	float Top()
	{
		return leftTop_.y;
	}	
	float Bot()
	{
		return leftBot_.y;
	}

	int ILeft()
	{
		return leftTop_.IntX();
	}	
	int IRight()
	{
		return rightTop_.IntX();
	}	
	int ITop()
	{
		return leftTop_.IntY();
	}	
	int IBot()
	{
		return leftBot_.IntY();
	}

	float4 GetLeftTop()
	{
		return leftTop_;
	}
	float4 GetRightTop()
	{
		return rightTop_;
	}
	float4 GetLeftBot()
	{
		return leftBot_;
	}
	float4 GetRightBot()
	{
		return rightBot_;
	}

private:
};
