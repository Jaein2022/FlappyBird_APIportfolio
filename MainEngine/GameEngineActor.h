#pragma once
#include "EngineEnum.h"

class GameEngineCollisionBody;
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor: public GameEngineNameBase
{
	friend GameEngineLevel;

	GameEngineLevel* parentLevel_;

	std::list<GameEngineRenderer*> allRenderers_;
	std::list<GameEngineCollisionBody*> allCollisionBodies_;
	
	float4 pos_;
	int renderOrder_;
	int updateOrder_;

protected:
	GameEngineActor();
	virtual ~GameEngineActor();

protected:
	GameEngineActor(const GameEngineActor& _other) = delete;
	GameEngineActor(GameEngineActor&& _other) noexcept = delete;

private:
	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete;


public:	
	float4 GetCameraPos();
	void ResetCollisionBodies();


public:	
	const float4 GetWorldPos() const
	{
		return pos_;
	}
	void SetWorldPos(const float4& _pos)//액터의 위치를 특정 지점으로 재설정.
	{
		pos_ = _pos;
	}
	void Move(const float4& _distance)	//액터의 이동 방향과 이동 거리 설정.
	{
		pos_ += _distance;
	}
	GameEngineLevel* const GetLevel()
	{
		return parentLevel_;
	}



protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) = 0;


	GameEngineRenderer* CreateRenderer(
		const std::string& _imageName,
		const std::string& _rendererName
	);
	GameEngineCollisionBody* CreateCollisionBody(
		const std::string& _collisionBodyName,
		CollisionBodyType _type,
		const float4& _size,
		const float4& _normalColor,
		const float4& _responseColor,
		int _thickness
	);


protected:
	void SetRenderOrder(int _renderOrder)
	{
		renderOrder_ = _renderOrder;
	}
	void SetUpdateOrder(int _updateOrder)
	{
		updateOrder_ = _updateOrder;
	}
	std::list<GameEngineCollisionBody*> GetCollisionBodies()
	{
		return allCollisionBodies_;
	}


private:
	void CheckCollision(GameEngineActor* _other);

private:
	void SetLevel(GameEngineLevel* _parentLevel)
	{
		parentLevel_ = _parentLevel;
	}
};

