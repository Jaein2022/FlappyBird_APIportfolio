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
	GameEngineActor* parentActor_;	//이 충돌체를 가진 부모 액터.
	float4 localPos_;	//액터 중심점에서 떨어진 거리.
	float4 size_;		//충돌체 크기. HLine이나 VLine은 x, y값이 2 고정.
	bool isCollided_;	//true == 충돌판정 발생함.
	
	CollisionBodyType type_;
	CollisionBody collisionBody_;
	float angle_;	//rRect 회전각도.
	bool isCameraEffect_;

	static bool isRenderingOn_;	//true: 모든 충돌체 렌더링 함. false: 모든 충돌체 렌더링 안 함.

	HPEN mainPen_;	//충돌체 렌더링 세팅값이 저장된 HPEN
	HPEN prevPen_;	//SelectObject()함수 반환값으로 잠시 받아두는 펜.
	COLORREF normalColor_;		//충돌 이전 색.
	COLORREF responseColor_;	//충돌 이후 색.
	int thickness_;	//충돌체 렌더러 선 두께.


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
	void SetTypeAndSize(CollisionBodyType _type, const float4& _size);
	void SetRrectAngle(float _degree);

public:


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

	void RotateRrect(float _angle)
	{
		this->SetRrectAngle(this->angle_ + _angle);
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

	static bool FRectToFRect(GameEngineCollisionBody* _fRectA, GameEngineCollisionBody* _fRectB);
	static bool FRectToHLine(GameEngineCollisionBody* _fRect, GameEngineCollisionBody* _hLine);
	static bool FRectToVLine(GameEngineCollisionBody* _fRect, GameEngineCollisionBody* _vLine);
	static bool FRectToRRect(GameEngineCollisionBody* _fRect, GameEngineCollisionBody* _rRect);

	static bool HLineToFRect(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _fRect);
	static bool HLineToHLine(GameEngineCollisionBody* _hLineA, GameEngineCollisionBody* _hLineB);
	static bool HLineToVLine(GameEngineCollisionBody* _rect, GameEngineCollisionBody* _vLine);
	static bool HLineToRRect(GameEngineCollisionBody* _hLine, GameEngineCollisionBody* _rRect);

	static bool VLineToFRect(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _fRect);
	static bool VLineToHLine(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _hLine);
	static bool VLineToVLine(GameEngineCollisionBody* _vLineA, GameEngineCollisionBody* _vLineB);
	static bool VLineToRRect(GameEngineCollisionBody* _vLine, GameEngineCollisionBody* _rRect);

	static bool RRectToFRect(GameEngineCollisionBody* _rRect, GameEngineCollisionBody* _fRect);
	static bool RRectToHLine(GameEngineCollisionBody* _rRect, GameEngineCollisionBody* _hLine);
	static bool RRectToVLine(GameEngineCollisionBody* _rRect, GameEngineCollisionBody* _vLine);
	static bool RRectToRRect(GameEngineCollisionBody* _rRectA, GameEngineCollisionBody* _rRectB);

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

