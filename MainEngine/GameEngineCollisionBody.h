#pragma once
#include "GameEngineEnum.h"

class GameEngineActor;
class GameEngineCollisionBody : public GameEngineNameBase
{
	//Friend Classes
	friend GameEngineActor;

	static std::function<bool(GameEngineCollisionBody*, GameEngineCollisionBody*)>
		checkCollisionFunctions_[static_cast<int>(CollisionBodyType::MAX)][static_cast<int>(CollisionBodyType::MAX)];

	//Member Variables
	GameEngineActor* parentActor_;
	float4 localPos_;
	float4 size_;
	
	CollisionBodyType type_;
	int groupIndex_;	



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

	static bool RectToLine(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right);
	static bool RectToRect(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right);

	static bool LineToLine(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right);
	static bool LineToRect(GameEngineCollisionBody* _left, GameEngineCollisionBody* _right);


	float4 GetWorldPos();

public:	//Getter, Setter, Templated Member Functions
	void SetGroup(int _order)
	{
		groupIndex_ = _order;
	}

	int GetGroup() const
	{
		return groupIndex_;
	}

	void SetType(CollisionBodyType _type)
	{
		type_ = _type;
	}

	int GetType()
	{
		return static_cast<int>(type_);
	}

	void SetSize(const float4& _size)
	{
		size_ = _size;
	}

	void SetLocalPos(const float4& _pos)
	{
		localPos_ = _pos;
	}



private://Member Function Headers


};

