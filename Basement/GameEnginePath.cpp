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
	//std::filesystem::path::stem()	확장자 제외한 파일명만 반환하는 함수.
	//filename() - extension() = stem()

	//std::filesystem::path::replace_extension() 확장자를 교체하는 함수.
	//교체할 확장자를 넣어주지 않으면 확장자가 제거된다.
	return path_.stem().string();
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}

bool GameEnginePath::IsExist()
{
	return std::filesystem::exists(path_);	//주어진 경로가 유효한지 판별하는 함수.
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}
