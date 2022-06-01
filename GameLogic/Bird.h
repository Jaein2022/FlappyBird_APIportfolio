#pragma once

class PlayLevel;
class Bird: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;
	friend PlayLevel;

	//Member Variables
	const float4 birdSize_;
	GameEngineRenderer* bird_Renderer_;
	GameEngineCollisionBody* bird_CollisionBody_;

	PlayLevel* parentPlayLevel_;
	const float initAscendingPower;
	float ascendingPower_;
	float increasedGravity_;
	float fallingSpeed_;

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
	const float4& GetSize() const
	{
		return birdSize_;
	}


private:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) override;
	void ControlMoving(float _deltaTime, const float _gravity, const float _playSpeed);

};

