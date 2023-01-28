#pragma once
#include "GameEngineLevel.h"

class GameEngineLevelManager
{
	static GameEngineLevelManager* inst_;
	std::map<std::string, GameEngineLevel*> allLevels_;

	GameEngineLevel* curLevel_;
	GameEngineLevel* nextLevel_;

private:
	GameEngineLevelManager();
	~GameEngineLevelManager();

protected:
	GameEngineLevelManager(const GameEngineLevelManager& _other) = delete;
	GameEngineLevelManager(GameEngineLevelManager&& _other) = delete;

private:
	GameEngineLevelManager& operator=(const GameEngineLevelManager& _other) = delete;
	GameEngineLevelManager& operator=(const GameEngineLevelManager&& _other) = delete;

public:
	void ChangeLevel(const std::string& _levelName);
	void Update();

public:
	static GameEngineLevelManager& GetInst()
	{
		return *inst_;
	}

	static void Destroy()
	{
		if (nullptr != inst_)
		{
			delete inst_;
			inst_ = nullptr;
		}
	}

	template<typename LevelType>
	void Create(const std::string& _levelName)
	{
		if (true == _levelName.empty())	//_levelName�� ���ٸ� ����.
		{
			GameEngineDebug::MsgBoxError("���� �̸��� �����ϴ�.");
			return;
		}

		GameEngineLevel* newLevel = new LevelType();

		newLevel->Initialize();
		newLevel->SetName(_levelName);

		std::pair<std::map<std::string, GameEngineLevel*>::iterator, bool> insertResult = allLevels_.insert(
			std::map<std::string, GameEngineLevel*>::value_type(
				_levelName, newLevel));

		if (false == insertResult.second)
		{
			GameEngineDebug::MsgBoxError(insertResult.first->first + ": �̹� ���� �̸��� ������ �����մϴ�.");
			return;
		}
	}

private:
	GameEngineLevel* Find(const std::string& _levelName);
};

