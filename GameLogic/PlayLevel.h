#pragma once

class Background;
class Bird;
class Pipe;
class UI;
class PlayLevel : public GameEngineLevel
{
	//플레이레벨.


	//Member Variables
	const float playSpeed_;

	Bird* bird_;
	Background* background_;

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

