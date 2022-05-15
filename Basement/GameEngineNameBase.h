#pragma once
#include "GameEngineObjectBase.h"

class GameEngineNameBase: public GameEngineObjectBase
{

	//Member Variables
	std::string name_;


public:
	GameEngineNameBase();
	~GameEngineNameBase();

protected:
	GameEngineNameBase(const GameEngineNameBase& _other) = delete;
	GameEngineNameBase(GameEngineNameBase&& _other) noexcept = delete;

private:
	GameEngineNameBase& operator=(const GameEngineNameBase& _other) = delete;
	GameEngineNameBase& operator=(const GameEngineNameBase&& _other) = delete;



public:	//Getter, Setter, Templated Member Functions
	void SetName(const std::string& _name)
	{
		name_ = _name;
	}

	std::string CopyName()
	{
		return name_;
	}

	const std::string& GetName()
	{
		return name_;
	}

	const char* GetNameChar()
	{
		return name_.c_str();
	}
};

