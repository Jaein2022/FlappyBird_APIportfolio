#include "PreCompile.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include "GameEngineSoundManager.h"

GameEnginePath::GameEnginePath(): path_(std::filesystem::current_path())
{
	//������ ���ÿ� ���� ��θ� �޾ƿ´�.
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _path): path_(_path)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEnginePath::GameEnginePath(const GameEnginePath& _other): path_(_other.path_)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEnginePath::GameEnginePath(GameEnginePath&& _other) noexcept: path_(_other.path_)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEnginePath::GameEnginePath(const std::string& _path): path_(_path)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ����Դϴ�.");
		return;
	}
}

GameEnginePath::GameEnginePath(const char* _path): path_(_path)
{
	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ����Դϴ�.");
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
	//std::filesystem::path::stem()-> Ȯ���� ������ ���ϸ� ��ȯ�ϴ� �Լ�.
	//filename() - extension() = stem()

	//std::filesystem::path::replace_extension()-> Ȯ���ڸ� ��ü�ϴ� �Լ�.
	//��ü�� Ȯ���ڸ� �־����� ������ Ȯ���ڰ� ���ŵȴ�.
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}

void GameEnginePath::MoveToParent(const std::string& _directoryName)
{
	while (path_.root_path() != path_)
	//std::filesystem::path::root_path()-> ���� �־��� ����� ��Ʈ ��θ� ��ȯ�ϴ� �Լ�.
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
		GameEngineDebug::MsgBoxError("�� �̻� ���� �ö� �� �����ϴ�.");
	}
	this->path_ = this->path_.parent_path();
}

void GameEnginePath::MoveToChild(const std::string& _directoryName)
{
	this->path_.append(_directoryName);
	if (false == std::filesystem::exists(this->path_))
	{
		GameEngineDebug::MsgBoxError(path_.string() + ": �������� �ʴ� ����Դϴ�.");
		return;
	}
}

std::vector<std::string> GameEnginePath::CollectAllFileNames()
{
	std::vector<std::string> allFileNames;
	allFileNames.reserve(30);

	if (false == std::filesystem::exists(path_))
	{
		GameEngineDebug::MsgBoxError(path_.string() + ": �������� �ʴ� ����Դϴ�.");
		return allFileNames;
	}

	std::filesystem::directory_iterator dirIter = std::filesystem::directory_iterator(path_);
	//directory_iterator: �̸� ������� ��γ� ���� Ȥ�� ������ ����Ű�� std::filesystem�� ���ͷ����� Ŭ����.

	for (const std::filesystem::directory_entry file : dirIter)
		//directory_entry: 
	{
		if (true == file.is_directory())
		{
			GameEngineDebug::MsgBoxError(file.path().string() + ": ������ �ƴ� �����Դϴ�.");
			return allFileNames;
		}

		allFileNames.push_back(file.path().string());
	}

	return allFileNames;
}


