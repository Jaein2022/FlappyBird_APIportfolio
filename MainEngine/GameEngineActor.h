#pragma once
#include "EngineEnum.h"

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
	void ResetCollisionBodies();


public:	//Getter, Setter, Templated Member Functions
	const float4 GetWorldPos() const
	{
		return pos_;
	}
	void SetWorldPos(const float4& _pos)		//������ ��ġ�� Ư�� �������� �缳��.
	{
		pos_ = _pos;
	}
	void Move(const float4& _distance)	//������ �̵� ����� �ӵ� ����.
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
		const float4& _collisionColor,
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


private://Member Function Headers
	void CheckCollision(GameEngineActor* _other);

private:
	void SetLevel(GameEngineLevel* _parentLevel)
	{
		parentLevel_ = _parentLevel;
	}
};

