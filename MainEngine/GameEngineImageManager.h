#pragma once

class GameEngineImage;
class GameEngineImageManager
{
	static GameEngineImageManager* inst_;
	std::map<std::string, GameEngineImage*> allImages_;


private:
	GameEngineImageManager();
	~GameEngineImageManager();

protected:
	GameEngineImageManager(const GameEngineImageManager& _other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _other) = delete;

private:
	GameEngineImageManager& operator=(const GameEngineImageManager& _other) = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager&& _other) = delete;

public:
					
	GameEngineImage* Load(const std::string& _path);							
	GameEngineImage* Load(const std::string& _name, const std::string& _path);	
	GameEngineImage* Find(const std::string& _name);							

public:
	static GameEngineImageManager& GetInst()
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

