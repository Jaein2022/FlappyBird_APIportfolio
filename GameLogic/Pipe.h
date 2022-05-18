#pragma once

class Pipe: public GameEngineActor
{
	//Friend Classes


	//Member Variables
	const int pipeWidth_;
	const int pipeHeight_;
	int pipeDistance_;

	GameEngineRenderer* topPipe_Renderer_;
	GameEngineCollisionBody* topPipe_CollisionBody_;

	GameEngineRenderer* botPipe_Renderer_;
	GameEngineCollisionBody* botPipe_CollisionBody_;

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
	void ReactCollision() override;


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

