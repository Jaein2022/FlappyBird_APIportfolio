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

	FMOD::System* soundSystem_; // FMOD가 제공해주는 인터페이스.
	//사운드파일 그 자체가 아니라 사운드를 통제하는 기본 인터페이스.

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
	void Load(const std::string& _path);		//파일이름 포함한 경로로 사운드파일 불러오기.				
	void Load(const std::string& _name, const std::string& _path); // 파일이름 따로 경로 따로 사운드파일 불러오기.
	GameEngineSound* Find(const std::string& _name);							

	GameEngineSoundPlayer* CreateSoundPlayer();	//사운드플레이어 생성.

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

