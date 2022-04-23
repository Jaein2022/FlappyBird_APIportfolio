#include "PreCompile.h"
#include "GameEngineDebug.h"

GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug()
{
}

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

void GameEngineDebug::MsgBoxError(const std::string& _errorMessage)
{
	MessageBoxA(nullptr, _errorMessage.c_str(), "Error!", MB_OK);
	assert(false);
}
