#pragma once

class PlayLevel;
class Pipe: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;
	friend PlayLevel;

	//Member Variables
	const int pipeWidth_;
	const int pipeHeight_;
	const int pipeDistance_;	//파이프 상하 간격.

	GameEngineRenderer* topPipe_Renderer_;
	GameEngineCollisionBody* topPipe_CollisionBody_;

	GameEngineRenderer* botPipe_Renderer_;
	GameEngineCollisionBody* botPipe_CollisionBody_;

	GameEngineCollisionBody* scoreCount_CollsionBody_;	

private:
	Pipe();
	~Pipe();

protected:
	Pipe(const Pipe& _other) = delete;
	Pipe(Pipe&& _other) noexcept = delete;

private:
	Pipe& operator=(const Pipe& _other) = delete;
	Pipe& operator=(const Pipe&& _other) = delete;


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

private:


};

