#pragma once

class Base: public GameEngineActor
{
	//Friend Classes
	friend class GameEngineLevel;

	//Member Variables
	const int baseWidth_;
	const int baseHeight_;
	GameEngineRenderer* baseRenderer_;
	GameEngineCollisionBody* baseCollisionBody_;

private:
	Base();
	~Base();

protected:
	Base(const Base& _other) = delete;
	Base(Base&& _other) noexcept = delete;

private:
	Base& operator=(const Base& _other) = delete;
	Base& operator=(const Base&& _other) = delete;


public:	//Member Function Headers



public:	//Getter, Setter, Templated Member Functions


private://Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) override;


};

