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
	if (true == _keyName.empty())	//�̸����� Ű�� ��������.
	{
		GameEngineDebug::MsgBoxError("Ű�� �̸��� �����ϴ�.");
		return;
	}

	if ('a' <= _keyValue && 'z' >= _keyValue)	//Ű�����δ� �빮�ڸ�.
	{
		_keyValue = toupper(_keyValue);
	}

	GameEngineKey* newKey = new GameEngineKey(_keyValue);
	if (nullptr == newKey)
	{
		GameEngineDebug::MsgBoxError("Ű ���� ����.");
		delete newKey;
		return;
	}

	std::pair<std::map<std::string, GameEngineKey*>::iterator, bool> insertResult = allKeys_.insert(
		std::map<std::string, GameEngineKey*>::value_type(
			_keyName, newKey));

	if (false == insertResult.second)
	{
		GameEngineDebug::MsgBoxError(insertResult.first->first + ": �̹� ���� �̸��� Ű�� �����մϴ�.");
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
		GameEngineDebug::MsgBoxError(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
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
		GameEngineDebug::MsgBoxError(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
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
		GameEngineDebug::MsgBoxError(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
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
		GameEngineDebug::MsgBoxError(_keyName + ": �׷� �̸��� Ű�� �������� �ʽ��ϴ�.");
		return false;
	}
	else
	{
		return findKeyIter->second->isFree_;
	}
}
