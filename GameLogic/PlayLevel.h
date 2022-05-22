#pragma once

class Background;
class Bird;
class Pipe;
class Base;
class UI;
class PlayLevel : public GameEngineLevel
{
	//플레이레벨.

	friend class GameEngineLevelManager;

	//Member Variables
	Bird* bird_;

	std::vector<Background*> backgrounds_;
	const int backgroundWidth_;
	const int backgroundCount_;

	std::vector<Base*> bases_;
	const int baseWidth_;
	const int baseCount_;

	std::vector<Pipe*> pipes_;
	const int pipeStartPosX_;
	const int pipeInterval_;	//파이프 좌우 간격.
	const int pipeCount_;



private:
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
	void Load() override;
	void UpdateLevel() override;
	void SwitchMode();

};

