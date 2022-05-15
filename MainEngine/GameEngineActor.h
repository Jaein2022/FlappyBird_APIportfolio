#pragma once
#include "GameEngineEnum.h"

class GameEngineCollisionBody;
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor: public GameEngineNameBase
{
	//Friend Classes
	friend GameEngineLevel;

	//Member Variables
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


public:	//Member Function Headers


	float4 GetCameraPos();


public:	//Getter, Setter, Templated Member Functions
	const float4 GetWorldPos() const
	{
		return pos_;
	}
	void SetWorldPos(const float4& _pos)		//액터의 위치를 특정 지점으로 재설정.
	{
		pos_ = _pos;
	}
	void Move(const float4& _distance)	//액터의 이동 방향과 속도 설정.
	{
		pos_ += _distance;
	}




protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void CheckCollision() = 0;

	GameEngineRenderer* CreateRenderer(
		const std::string& _imageName,
		const std::string& _rendererName
	);
	GameEngineCollisionBody* CreateCollisionBody(
		const std::string& _collisionBodyName,
		const float4& _color,
		CollisionBodyType _type
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


private://Member Function Headers


};

