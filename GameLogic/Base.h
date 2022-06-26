#pragma once

class Base: public GameEngineActor
{
	friend class GameEngineLevel;

	const float4 baseSize_;
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

