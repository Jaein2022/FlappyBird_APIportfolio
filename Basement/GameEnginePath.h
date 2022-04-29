#pragma once

class GameEnginePath
{
	//std::fileSystem�� ������� Ư�� ������ ��ο� ���ϸ�, Ȯ���ڸ� �����ؼ� ���ҽ� �ε��� �����ϴ� Ŭ����.
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
	std::string GetFullPath();	//���� �̸� ������ ��ü ��θ� �޾ƿ��� �Լ�.

	//fileName() - extension() = stem()
	static std::string GetFileName(const std::string& _path);	//�־��� ��ο��� ���� �̸��� ��ȯ�ϴ� �Լ�.
	std::string GetFileName();	//���� ��ο��� ���� �̸��� ��ȯ�ϴ� �Լ�.
	std::string GetStem();		//Ȯ���� ������ ���� �̸��� ��ȯ�ϴ� �Լ�.
	std::string GetExtension();	//������ Ȯ���ڸ� ��ȯ�ϴ� �Լ�.


public:	
	void MoveToParent(const std::string& _directoryName);
	void MoveToChild(const std::string& _directoryName);
	std::vector<std::string> CollectAllFileNames();


private:

};

