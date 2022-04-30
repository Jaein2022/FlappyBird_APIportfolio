#pragma once

class BackGround;
class Bird;
class Pipe;
class UI;
class PlayLevel : public GameEngineLevel
{



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
	void Load() override;


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

