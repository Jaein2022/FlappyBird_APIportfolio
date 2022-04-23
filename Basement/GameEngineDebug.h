#pragma once

class GameEngineDebug
{

public:
	GameEngineDebug();
	~GameEngineDebug();

protected:
	GameEngineDebug(const GameEngineDebug& _other) = delete;
	GameEngineDebug(GameEngineDebug&& _other) noexcept = delete;

private:
	GameEngineDebug& operator=(const GameEngineDebug& _other) = delete;
	GameEngineDebug& operator=(const GameEngineDebug&& _other) = delete;


public:	//Member Function Headers
	static void LeakCheckOn();
	static void MsgBoxError(const std::string& _errorMessage);
};

