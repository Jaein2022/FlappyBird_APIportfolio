#pragma once
#include "GameEngineEnum.h"

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
	
	CollisionBodyType type_;
	bool isCameraEffect_;

	HPEN pen_;
	HBRUSH brush_;
	COLORREF color_;

private:
	GameEngineCollisionBody(GameEngineActor* _actor);
	~GameEngineCollisionBody();

protected:
	GameEngineCollisionBody(const GameEngineCollisionBody& _other) = delete;
	GameEngineCollisionBody(GameEngineCollisionBody&& _other) noexcept = delete;

private:
	GameEngineCollisionBody& operator=(const GameEngineCollisionBody& _other) = delete;
	GameEngineCollisionBody& operator=(const GameEngineCollisionBody&& _other) = delete;


public:	//Member Function Headers
	static void Initialize();

	static bool RectToHLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _hLine);
	static bool RectToRect(GameEngineCollisionBody* _a, GameEngineCollisionBody* _b);

	static bool PointToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine);

	bool CheckCollision(GameEngineCollisionBody* _other);
	float4 GetWorldPos();
	GameEngineRect GetRect();

	void Render();

public:	//Getter, Setter, Templated Member Functions

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

	void SetSize(const float4& _size)
	{
		size_ = _size;

		if (CollisionBodyType::HLine == type_ && 0.f < size_.y )
		{
			GameEngineDebug::MsgBoxError("HLine 충돌체는 세로길이를 가질 수 없습니다.");
		}
	}

	float4 GetSize()
	{
		return size_;
	}

	void SetLocalPos(const float4& _pos)
	{
		localPos_ = _pos;
	}

	void SetColor(const float4& _color)
	{
		color_ = RGB(
			static_cast<int>(_color.r * 255.f),
			static_cast<int>(_color.g * 255.f),
			static_cast<int>(_color.b * 255.f)
		);

		switch (type_)
		{
		case CollisionBodyType::Rect:
			brush_ = CreateSolidBrush(color_);
			break;

		case CollisionBodyType::HLine:
			pen_ = CreatePen(PS_SOLID, 1, color_);
			break;
		
		default:
			break;
		}
	}

private://Member Function Headers


};

