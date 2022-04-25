#pragma once

class GameEngineRenderer: public GameEngineNameBase
{
	//Friend Classes
	friend class GameEngineActor;

	//Member Variables


public:
	GameEngineRenderer();
	~GameEngineRenderer();

protected:
	GameEngineRenderer(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;

private:
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete;


public:	//Member Function Headers



public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

