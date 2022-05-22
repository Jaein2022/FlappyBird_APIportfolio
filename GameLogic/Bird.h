#pragma once

class PlayLevel;
class Bird: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;
	friend PlayLevel;

	//Member Variables
	GameEngineRenderer* bird_Renderer_;
	GameEngineCollisionBody* bird_CollisionBody_;

private:
	Bird();
	~Bird();

protected:
	Bird(const Bird& _other) = delete;
	Bird(Bird&& _other) noexcept = delete;

private:
	Bird& operator=(const Bird& _other) = delete;
	Bird& operator=(const Bird&& _other) = delete;

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

