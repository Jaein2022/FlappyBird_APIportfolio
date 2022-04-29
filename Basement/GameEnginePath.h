#pragma once

class GameEnginePath
{
	//std::fileSystem을 기반으로 특정 파일의 경로와 파일명, 확장자를 관리해서 리소스 로딩을 지원하는 클래스.
	//https://en.cppreference.com/w/cpp/filesystem/path
	
protected: //Member Variables
	std::filesystem::path path_;


public:
	GameEnginePath();
	~GameEnginePath();

protected:
	GameEnginePath(std::filesystem::path _path);
	GameEnginePath(const GameEnginePath& _other);
	GameEnginePath(GameEnginePath&& _other) noexcept;

private:
	GameEnginePath& operator=(const GameEnginePath& _other) = delete;
	GameEnginePath& operator=(const GameEnginePath&& _other) = delete;


public:
	std::string GetFullPath();	//파일 이름 포함한 전체 경로를 받아오는 함수.

	//fileName() - extension() = stem()
	static std::string GetFileName(const std::string& _path);	//주어진 경로에서 파일 이름만 반환하는 함수.
	std::string GetFileName();	//현재 경로에서 파일 이름만 반환하는 함수.
	std::string GetStem();		//확장자 제외한 파일 이름을 반환하는 함수.
	std::string GetExtension();	//파일의 확장자만 반환하는 함수.


public:	
	void MoveToParent(const std::string& _directoryName);
	void MoveToChild(const std::string& _directoryName);
	std::vector<std::string> CollectAllFileNames();


private:

};

