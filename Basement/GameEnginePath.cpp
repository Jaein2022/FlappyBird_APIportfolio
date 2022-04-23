#include "PreCompile.h"
#include "GameEnginePath.h"

GameEnginePath::GameEnginePath(): path_("")
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _path): path_(_path)
{
}

GameEnginePath::GameEnginePath(const GameEnginePath& _other): path_(_other.path_)
{
}

GameEnginePath::GameEnginePath(GameEnginePath&& _other) noexcept: path_(_other.path_)
{
}

GameEnginePath::~GameEnginePath()
{
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
	//std::filesystem::path::stem()	Ȯ���� ������ ���ϸ� ��ȯ�ϴ� �Լ�.
	//filename() - extension() = stem()

	//std::filesystem::path::replace_extension() Ȯ���ڸ� ��ü�ϴ� �Լ�.
	//��ü�� Ȯ���ڸ� �־����� ������ Ȯ���ڰ� ���ŵȴ�.
	return path_.stem().string();
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}

bool GameEnginePath::IsExist()
{
	return std::filesystem::exists(path_);	//�־��� ��ΰ� ��ȿ���� �Ǻ��ϴ� �Լ�.
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}
