#pragma once

class Bird: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;

	//Member Variables
	GameEngineRenderer* birdRenderer_;
	GameEngineCollisionBody* birdCollisionBody_;

private:
	Bird();
	~Bird();

protected:
	Bird(const Bird& _other) = delete;
	Bird(Bird&& _other) noexcept = delete;

private:
	Bird& operator=(const Bird& _other) = delete;
	Bird& operator=(const Bird&& _other) = delete;

private:	//Member Function Headers


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void CheckCollision() override;


};

