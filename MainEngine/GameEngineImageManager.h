#pragma once

class GameEngineImage;
class GameEngineImageManager
{
	static GameEngineImageManager* inst_;
	std::map<std::string, GameEngineImage*> allImages_;
	GameEngineImage* frontBufferImage_;	//현재 윈도우 이미지.
	GameEngineImage* backBufferImage_;	//백버퍼 이미지.

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
	void InitializeWindowImage(const HDC& _windowHDC);
	void CopyToFrontBuffer();
	

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

	GameEngineImage* GetBackBufferImage()
	{
		return backBufferImage_;
	}

};

