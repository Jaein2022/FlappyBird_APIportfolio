#pragma once

class Base: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;

	//Member Variables
	const int baseWidth_;
	const int baseHeight_;
	GameEngineRenderer* base_Renderer_;
	GameEngineCollisionBody* base_CollisionBody_;

private:
	Base();
	~Base();

protected:
	Base(const Base& _other) = delete;
	Base(Base&& _other) noexcept = delete;

private:
	Base& operator=(const Base& _other) = delete;
	Base& operator=(const Base&& _other) = delete;


public:	



public:


private:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) override;


};

