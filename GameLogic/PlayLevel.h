#pragma once

class PlayLevel : public GameEngineLevel
{
	//Friend Classes


	//Member Variables


public:
	PlayLevel();
	~PlayLevel();

protected:
	PlayLevel(const PlayLevel& _other) = delete;
	PlayLevel(PlayLevel&& _other) noexcept = delete;

private:
	PlayLevel& operator=(const PlayLevel& _other) = delete;
	PlayLevel& operator=(const PlayLevel&& _other) = delete;


public:	//Member Function Headers



public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

