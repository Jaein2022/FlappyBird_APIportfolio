#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float TAU;	//Tau
	static const float DegreeToRadian;	//60분법->호도법(0.017453...)
	static const float RadianToDegree;	//호도법->60분법(57.29577...)
};

class float4
{
public:
	//자주 사용하는 숫자 조합을 미리 만들어놓으면 생성자 호출하는 연산비용을 아낄 수 있다.
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

		NextVector.x_ = _originVector.x_ * cosf(_radian) - _originVector.y_ * sinf(_radian);
		NextVector.y_ = _originVector.x_ * sinf(_radian) + _originVector.y_ * cosf(_radian);

		return NextVector;
	}

	static float4 ConvertToDegree(float _degree)
	{
		return ConvertToRadian(_degree * GameEngineMath::DegreeToRadian);
	}
	static float4 ConvertToRadian(float _radian)		//벡터가 0도일때 벡터를 회전시키는 공식.
	{
		return float4(cosf(_radian), sinf(_radian));
	}
	static float4 ConvertToRadian(float4 vector, float _radian)
	{
		return float4(cosf(_radian), sinf(_radian));
	}

public:
	//익명으로 유니온을 선언하고 그 안에 구조체를 두면, 
	//유니온처럼 메모리를 공용으로 활용할 수 있는 클래스 멤버 구조체를 사용할 수 있다.
	union
	{
		struct
		{
			float x_;
			float y_;
			float z_;
			float w_;	//연산시 w_값 증감 주의.
		};
	};

	float4() : x_(0.f), y_(0.f), z_(0.f), w_(1.f)
	{
	}

	float4(const float4& _other) : x_(_other.x_), y_(_other.y_), z_(_other.z_), w_(_other.w_)
	{
	}

	float4(float4&& _value) noexcept : x_(_value.x_), y_(_value.y_), z_(_value.z_), w_(_value.w_)
	{
	}

	float4(int _x, int _y) : x_(static_cast<float>(_x)), y_(static_cast<float>(_y)), z_(0.f), w_(1.f)
	{
	}

	float4(float _x, float _y) : x_(_x), y_(_y), z_(0.f), w_(1.f)
	{
	}

	float4(int _x, int _y, int _z)
		: x_(static_cast<float>(_x)), y_(static_cast<float>(_y)), z_(static_cast<float>(_z)), w_(1.0f)
	{
	}

	float4(float _x, float _y, float _z, float _w = 1.f) : x_(_x), y_(_y), z_(_z), w_(_w)
	{
	}

	~float4()
	{
	}


	float4& operator=(const float4& _other)
	{
		this->x_ = _other.x_;
		this->y_ = _other.y_;
		this->z_ = _other.z_;
		this->w_ = _other.w_;
		return *this;
	}

	float4 operator+(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x_ = this->x_ + _other.x_;
		ReturnValue.y_ = this->y_ + _other.y_;
		ReturnValue.z_ = this->z_ + _other.z_;
		ReturnValue.w_ = this->w_ + _other.w_;

		return ReturnValue;
	}

	float4 operator-(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x_ = this->x_ - _other.x_;
		ReturnValue.y_ = this->y_ - _other.y_;
		ReturnValue.z_ = this->z_ - _other.z_;
		ReturnValue.w_ = this->w_ - _other.w_;

		return ReturnValue;
	}

	float4 operator*(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x_ = this->x_ * _other.x_;
		ReturnValue.y_ = this->y_ * _other.y_;
		ReturnValue.z_ = this->z_ * _other.z_;
		ReturnValue.w_ = this->w_ * _other.w_;

		return ReturnValue;
	}

	float4 operator/(const float4 _other) const
	{
		float4 ReturnValue;
		ReturnValue.x_ = this->x_ / _other.x_;
		ReturnValue.y_ = this->y_ / _other.y_;
		ReturnValue.z_ = this->z_ / _other.z_;
		ReturnValue.w_ = this->w_ / _other.w_;

		return ReturnValue;
	}

	float4& operator+=(const float4 _other)
	{
		this->x_ = this->x_ + _other.x_;
		this->y_ = this->y_ + _other.y_;
		this->z_ = this->z_ + _other.z_;
		this->w_ = this->w_ + _other.w_;

		return *this;
	}

	float4& operator-=(const float4 _other)
	{
		this->x_ = this->x_ - _other.x_;
		this->y_ = this->y_ - _other.y_;
		this->z_ = this->z_ - _other.z_;
		this->w_ = this->w_ - _other.w_;

		return *this;
	}

	float4& operator*=(const float4 _other)
	{
		this->x_ = this->x_ * _other.x_;
		this->y_ = this->y_ * _other.y_;
		this->z_ = this->z_ * _other.z_;
		this->w_ = this->w_ * _other.w_;

		return *this;
	}

	float4& operator/=(const float4 _other)
	{
		this->x_ = this->x_ / _other.x_;
		this->y_ = this->y_ / _other.y_;
		this->z_ = this->z_ / _other.z_;
		this->w_ = this->w_ / _other.w_;

		return *this;
	}

	float4 operator*(const float _value) const
	{
		float4 ReturnValue;
		ReturnValue.x_ = this->x_ * _value;
		ReturnValue.y_ = this->y_ * _value;
		ReturnValue.z_ = this->z_ * _value;
		ReturnValue.w_ = this->w_ * _value;

		return ReturnValue;
	}

	//x, y만 비교.
	bool operator==(const float4& _value) const	
	{
		return (this->x_ == _value.x_ && this->y_ == _value.y_);
	}

	//x, y만 비교.
	bool operator!=(const float4& _value) const	
	{
		return (this->x_ != _value.x_ || this->y_ != _value.y_);
	}

	float Half_X()
	{
		return x_ * 0.5f;
	}

	float Half_Y()
	{
		return y_ * 0.5f;
	}

	float Half_Z()
	{
		return z_ * 0.5f;
	}

	float4 Half()
	{
		return { Half_X(), Half_Y(), Half_Z() };
	}

	int IntX() const
	{
		return static_cast<int>(x_);
	}

	int IntY() const
	{
		return static_cast<int>(y_);
	}

	int IntZ() const
	{
		return static_cast<int>(z_);
	}

	int Half_IntX()
	{
		return static_cast<int>(x_ * 0.5f);
	}

	int Half_IntY()
	{
		return static_cast<int>(y_ * 0.5f);
	}

	int Half_IntZ()
	{
		return static_cast<int>(z_ * 0.5f);
	}

};