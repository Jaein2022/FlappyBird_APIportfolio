#pragma once

class GameEngineSoundPlayer;
class PlayLevel;
class Bird: public GameEngineActor
{
	friend class GameEngineLevel;
	friend PlayLevel;

	const float4 birdSize_;
	GameEngineRenderer* bird_Renderer_;
	GameEngineCollisionBody* bird_CollisionBody_;

	PlayLevel* parentPlayLevel_;
	const float initAscendingSpeed_;	//스페이스바 눌렀을때 입력되는 초기 상승 속도.
	float fallingSpeed_;				//현재 추락 속도.
	float initAscendingSecond_;
	float ascendingSecond_;

	GameEngineSoundPlayer* bird_SoundPlayer_;


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
	const float GetAngle() const
	{
		return bird_Renderer_->GetAngle();
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
	void SetAngle(float _deltaTime);		//버드 렌더러 기울기 조정.
};

