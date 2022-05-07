#pragma once

class Base: public GameEngineActor
{
	//Friend Classes


	//Member Variables


public:
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
	void Initialize() override;
	void Update() override;
	void Render() override;
	void CheckCollision() override;


private://Member Function Headers


};

