#include "PreCompile.h"
#include "GameEngineInput.h"

GameEngineInput* GameEngineInput::inst_ = new GameEngineInput();

void GameEngineInput::GameEngineKey::Update()
{
	if (0 != GetAsyncKeyState(keyValue_))
	{
		if (false == isPressed_)
		{
			isDown_ = true;
			isPressed_ = true;
			isUp_ = false;
			isFree_ = false;
		}
		else if (true == isPressed_)
		{
			isDown_ = false;
			isPressed_ = true;
			isUp_ = false;
			isFree_ = false;
		}
	}
	else
	{
		if (true == isPressed_)
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = true;
			isFree_ = true;
		}
		else if (false == isPressed_)
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = false;
			isFree_ = true;
		}
	}
}

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
	for (std::pair<std::string, GameEngineKey*> keyPair : allKeys_)
	{
		delete keyPair.second;
		keyPair.second = nullptr;
	}
}

void GameEngineInput::CreateKey(const std::string& _keyName, int _keyValue)
{
	if (true == _keyName.empty())	//이름없는 키는 생성금지.
	{
		GameEngineDebug::MsgBoxError("키의 이름이 없습니다.");
		return;
	}

	if ('a' <= _keyValue && 'z' >= _keyValue)	//키값으로는 대문자만.
	{
		_keyValue = toupper(_keyValue);
	}

	GameEngineKey* newKey = new GameEngineKey(_keyValue);
	if (nullptr == newKey)
	{
		GameEngineDebug::MsgBoxError("키 생성 실패.");
		delete newKey;
		return;
	}

	std::pair<std::map<std::string, GameEngineKey*>::iterator, bool> insertResult = allKeys_.insert(
		std::map<std::string, GameEngineKey*>::value_type(
			_keyName, newKey));

	if (false == insertResult.second)
	{
		GameEngineDebug::MsgBoxError(insertResult.first->first + ": 이미 같은 이름의 키가 존재합니다.");
		return;
	}
}

void GameEngineInput::Update()
{
	for (std::pair<std::string, GameEngineKey*> keyPair : allKeys_)
	{
		keyPair.second->Update();
	}
}

bool GameEngineInput::IsDown(const std::string& _keyName)
{
	std::map<std::string, GameEngineKey*>::iterator findKeyIter = allKeys_.find(_keyName);

	if (allKeys_.end() == findKeyIter)
	{
		GameEngineDebug::MsgBoxError(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}
	else
	{
		return findKeyIter->second->isDown_;
	}
}

bool GameEngineInput::IsPressed(const std::string& _keyName)
{
	std::map<std::string, GameEngineKey*>::iterator findKeyIter = allKeys_.find(_keyName);

	if (allKeys_.end() == findKeyIter)
	{
		GameEngineDebug::MsgBoxError(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}
	else
	{
		return findKeyIter->second->isPressed_;
	}
}

bool GameEngineInput::IsUp(const std::string& _keyName)
{
	std::map<std::string, GameEngineKey*>::iterator findKeyIter = allKeys_.find(_keyName);

	if (allKeys_.end() == findKeyIter)
	{
		GameEngineDebug::MsgBoxError(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}
	else
	{
		return findKeyIter->second->isUp_;
	}
}

bool GameEngineInput::IsFree(const std::string& _keyName)
{
	std::map<std::string, GameEngineKey*>::iterator findKeyIter = allKeys_.find(_keyName);

	if (allKeys_.end() == findKeyIter)
	{
		GameEngineDebug::MsgBoxError(_keyName + ": 그런 이름의 키가 존재하지 않습니다.");
		return false;
	}
	else
	{
		return findKeyIter->second->isFree_;
	}
}
