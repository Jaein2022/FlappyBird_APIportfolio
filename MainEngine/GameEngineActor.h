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
	GameEngineRenderer* CreateRenderer(
		const std::string& _imageName,
		const std::string& _rendererName
	);
	GameEngineCollisionBody* CreateCollisionBody(
		const std::string& _collisionBodyName,
		int _collisionOrder,
		CollisionBodyType _type
	);

	float4 GetCameraPos();


public:	//Getter, Setter, Templated Member Functions
	const float4 GetPos() const
	{
		return pos_;
	}
	void SetPos(const float4& _pos)		//������ ��ġ�� Ư�� �������� �缳��.
	{
		pos_ = _pos;
	}
	void Move(const float4& _distance)	//������ �̵� ����� �ӵ� ����.
	{
		pos_ += _distance;
	}




protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void CheckCollision() = 0;

protected:
	void SetRenderOrder(int _renderOrder)
	{
		renderOrder_ = _renderOrder;
	}
	void SetUpdateOrder(int _updateOrder)
	{
		updateOrder_ = _updateOrder;
	}


private://Member Function Headers


};

