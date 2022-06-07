#include "PreCompile.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include "GameEngineSoundManager.h"

GameEnginePath::GameEnginePath(): path_(std::filesystem::current_path())
{
	//생성과 동시에 현재 경로를 받아온다.
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _path): path_(_path)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 경로입니다.");
		return;
	}
}

GameEnginePath::GameEnginePath(const GameEnginePath& _other): path_(_other.path_)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 경로입니다.");
		return;
	}
}

GameEnginePath::GameEnginePath(GameEnginePath&& _other) noexcept: path_(_other.path_)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 경로입니다.");
		return;
	}
}

GameEnginePath::GameEnginePath(const std::string& _path): path_(_path)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 경로입니다.");
		return;
	}
}

GameEnginePath::GameEnginePath(const char* _path): path_(_path)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 경로입니다.");
		return;
	}
}

GameEnginePath::~GameEnginePath()
{
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}

std::string GameEnginePath::GetFileName(const std::string& _path)
{
	std::filesystem::path newPath = _path;
	return newPath.filename().string();
}

std::string GameEnginePath::GetFileName()
{
	return path_.filename().string();
}

std::string GameEnginePath::GetStem()
{
	return path_.stem().string();
	//std::filesystem::path::stem()-> 확장자 제외한 파일명만 반환하는 함수.
	//filename() - extension() = stem()

	//std::filesystem::path::replace_extension()-> 확장자를 교체하는 함수.
	//교체할 확장자를 넣어주지 않으면 확장자가 제거된다.
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}

void GameEnginePath::MoveToParent(const std::string& _directoryName)
{
	while (path_.root_path() != path_)
	//std::filesystem::path::root_path()-> 현재 주어진 경로의 루트 경로를 반환하는 함수.
	{
		if (_directoryName == path_.filename().string())
		{
			return;
		}
		this->path_ = this->path_.parent_path();
	}
}

void GameEnginePath::MoveToParent()
{
	if (path_.root_path() == path_)
	{
		GameEngineDebug::MsgBoxError("더 이상 위로 올라갈 수 없습니다.");
	}
	this->path_ = this->path_.parent_path();
}

void GameEnginePath::MoveToChild(const std::string& _directoryName)
{
	this->path_.append(_directoryName);
	if (false == std::filesystem::exists(this->path_))
	{
		GameEngineDebug::MsgBoxError(path_.string() + ": 존재하지 않는 경로입니다.");
		return;
	}
}

std::vector<std::string> GameEnginePath::CollectAllFileNames()
{
	std::vector<std::string> allFileNames;
	allFileNames.reserve(30);

	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError(path_.string() + ": 존재하지 않는 경로입니다.");
		return allFileNames;
	}

	std::filesystem::directory_iterator dirIter = std::filesystem::directory_iterator(path_);
	//directory_iterator: 이름 순서대로 경로내 폴더 혹은 파일을 가리키는 std::filesystem의 이터레이터 클래스.

	for (const std::filesystem::directory_entry file : dirIter)
		//directory_entry: 
	{
		if (true == file.is_directory())
		{
			GameEngineDebug::MsgBoxError(file.path().string() + ": 파일이 아닌 폴더입니다.");
			return allFileNames;
		}

		allFileNames.push_back(file.path().string());
	}

	return allFileNames;
}


