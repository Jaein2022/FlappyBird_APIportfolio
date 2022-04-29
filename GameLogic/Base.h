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



private://Member Function Headers


};

