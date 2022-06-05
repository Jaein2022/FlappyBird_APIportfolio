#pragma once
#include "EngineEnum.h"

class GameEngineActor;
class GameEngineCollisionBody : public GameEngineNameBase
{
	//Friend Classes
	friend GameEngineActor;


	static std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
		collisionFunctions_[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)];

	//Member Variables
	GameEngineActor* parentActor_;
	float4 localPos_;
	float4 size_;
	bool isCollided_; //true == 충돌판정 발생함.
	
	CollisionBodyType type_;
	bool isCameraEffect_;

	static bool isRenderingOn_;

	HPEN mainPen_;
	HPEN prevPen_;
	COLORREF normalColor_;
	COLORREF responseColor_;
	int thickness_;


private:
	GameEngineCollisionBody(GameEngineActor* _actor);
	~GameEngineCollisionBody();

protected:
	GameEngineCollisionBody(const GameEngineCollisionBody& _other) = delete;
	GameEngineCollisionBody(GameEngineCollisionBody&& _other) noexcept = delete;

private:
	GameEngineCollisionBody& operator=(const GameEngineCollisionBody& _other) = delete;
	GameEngineCollisionBody& operator=(const GameEngineCollisionBody&& _other) = delete;

public:
	static void Initialize();

	void Render();
	void Respond(bool _isExcluded = false);

public:

	void SetType(CollisionBodyType _type)
	{
		type_ = _type;
	}

	int GetTypeInt()
	{
		return static_cast<int>(type_);
	}

	CollisionBodyType GetType()
	{
		return type_;
	}
	GameEngineActor* const GetActor()
	{
		return parentActor_;
	}

	void SetCameraEffectOn()
	{
		isCameraEffect_ = true;
	}

	void SetCameraEffectOff()
	{
		isCameraEffect_ = false;
	}

	void SetLocalPos(const float4& _pos)
	{
		localPos_ = _pos;
	}

	void SetSize(const float4& _size)
	{
		size_ = _size;

		if (CollisionBodyType::HLine == type_ && 0.f < size_.y)
		{
			GameEngineDebug::MsgBoxError("HLine 충돌체는 세로길이를 가질 수 없습니다.");
		}

		if (CollisionBodyType::VLine == type_ && 0.f < size_.x)
		{
			GameEngineDebug::MsgBoxError("VLine 충돌체는 가로길이를 가질 수 없습니다.");
		}
	}

	float4 GetSize()
	{
		return size_;
	}

	static void SwitchRendering()
	{
		isRenderingOn_ = !isRenderingOn_;
	}

private:
	void SwitchColor();
	bool CheckCollision(GameEngineCollisionBody* _other);
	float4 GetWorldPos();
	GameEngineRect GetRect();
	void Reset();

private:
	static bool RectToRect(GameEngineCollisionBody* _rectA, GameEngineCollisionBody* _rectB);
	static bool RectToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine);
	static bool RectToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine);

	static bool HLineToRect(GameEngineCollisionBody* _hLineA, GameEngineCollisionBody* _hLineB);
	static bool HLineToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine);
	static bool HLineToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine);

	static bool VLineToRect(GameEngineCollisionBody* _vLineA, GameEngineCollisionBody* _vLineB);
	static bool VLineToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine);
	static bool VLineToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine);

private:

	void SetPen(const float4& _normalColor, const float4& _responseColor, int _thickness)
	{
		normalColor_ = RGB(
			static_cast<int>(_normalColor.r * 255.f),
			static_cast<int>(_normalColor.g * 255.f),
			static_cast<int>(_normalColor.b * 255.f)
		);
		responseColor_ = RGB(
			static_cast<int>(_responseColor.r * 255.f),
			static_cast<int>(_responseColor.g * 255.f),
			static_cast<int>(_responseColor.b * 255.f)
		);
		thickness_ = _thickness;
		mainPen_ = CreatePen(PS_SOLID, thickness_, normalColor_);
	}



};

