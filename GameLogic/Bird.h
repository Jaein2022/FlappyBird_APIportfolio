#pragma once

class Bird: public GameEngineActor
{
	//Friend Classes


	//Member Variables


public:
	Bird();
	~Bird();

protected:
	Bird(const Bird& _other) = delete;
	Bird(Bird&& _other) noexcept = delete;

private:
	Bird& operator=(const Bird& _other) = delete;
	Bird& operator=(const Bird&& _other) = delete;


public:	//Member Function Headers



public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};
