#pragma once
#include "../ThirdParty/Include/FMOD/fmod.hpp"

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")	
#else									
#pragma comment(lib, "fmod_vc.lib")		
#endif // DEBUG

class GameEngineSoundPlayer;
class GameEngineSound;
class GameEngineSoundManager
{
	//Friend Classes
	friend GameEngineSound;
	friend GameEngineSoundPlayer;

	//Member Variables
	static GameEngineSoundManager* inst_;

	FMOD::System* soundSystem_; // FMOD�� �������ִ� �������̽�.
	//�������� �� ��ü�� �ƴ϶� ���带 �����ϴ� �⺻ �������̽�.

	std::map<std::string, GameEngineSound*> allSound_;
	std::list<GameEngineSoundPlayer*> allSoundPlayers_;


private:
	GameEngineSoundManager();
	~GameEngineSoundManager();

protected:
	GameEngineSoundManager(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager(GameEngineSoundManager&& _other) = delete;

private:
	GameEngineSoundManager& operator=(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager& operator=(const GameEngineSoundManager&& _other) = delete;

public:
	void Initialize();							
	void Update();								
	void Load(const std::string& _path);		//�����̸� ������ ��η� �������� �ҷ�����.				
	void Load(const std::string& _name, const std::string& _path); // �����̸� ���� ��� ���� �������� �ҷ�����.
	GameEngineSound* Find(const std::string& _name);							

	GameEngineSoundPlayer* CreateSoundPlayer();	//�����÷��̾� ����.

public:
	static GameEngineSoundManager& GetInst()
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

};

