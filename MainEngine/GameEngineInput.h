#pragma once

class GameEngineInput
{
	class GameEngineKey
	{
		friend GameEngineInput;

		bool isDown_;
		bool isPressed_;
		bool isUp_;
		bool isFree_;
		const int keyValue_;

	public:
		GameEngineKey(int _keyValue)
			: isDown_(false),
			isPressed_(false),
			isUp_(false),
			isFree_(true),
			keyValue_(_keyValue)
		{
		}

	public:
		void Update();

	};


	//Member Variables
	static GameEngineInput* inst_;

	std::map<std::string, GameEngineKey*> allKeys_;

public:
	GameEngineInput();
	~GameEngineInput();

protected:
	GameEngineInput(const GameEngineInput& _other) = delete;
	GameEngineInput(GameEngineInput&& _other) noexcept = delete;

private:
	GameEngineInput& operator=(const GameEngineInput& _other) = delete;
	GameEngineInput& operator=(const GameEngineInput&& _other) = delete;


public:	//Member Function Headers
	void CreateKey(const std::string& _keyName, int _keyValue);
	void Update();
	bool IsDown(const std::string& _keyName);
	bool IsPressed(const std::string& _keyName);
	bool IsUp(const std::string& _keyName);
	bool IsFree(const std::string& _keyName);


public:	//Getter, Setter, Templated Member Functions
	static GameEngineInput& GetInst()
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


private://Member Function Headers


};

