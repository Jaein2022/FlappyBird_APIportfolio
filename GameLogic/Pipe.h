#pragma once

class Pipe: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;

	//Member Variables
	const int pipeWidth_;
	const int pipeHeight_;
	const int pipeDistance_;	//파이프 상하 간격.

	GameEngineRenderer* topPipe_Renderer_;
	GameEngineCollisionBody* topPipe_CollisionBody_;

	GameEngineRenderer* botPipe_Renderer_;
	GameEngineCollisionBody* botPipe_CollisionBody_;

	//카메라 구조 제대로 적용되면 UI로 옮길 것.
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


private:	//Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) override;


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

