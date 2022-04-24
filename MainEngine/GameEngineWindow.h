#pragma once

class GameEngineWindow
{
	//������ ���� �� ��������� �� ��Ĵ�� ���� Ŭ����.

	//Member Variables
	static GameEngineWindow* inst_;

	HINSTANCE instanceHandle_;
	HWND windowHandle_;
	std::string windowClassName_;
	std::string windowTitle_;
	float4 windowPos_;
	float4 windowSize_;


private:
	// �����츦 �ƹ��� �����Ҽ� ���� �ϱ� ���� �⺻�����ڸ� private���� ���´�.
	GameEngineWindow();
	~GameEngineWindow();

protected:
	GameEngineWindow(const GameEngineWindow& _other) = delete;
	GameEngineWindow(GameEngineWindow&& _other) noexcept = delete;

private:
	GameEngineWindow& operator=(const GameEngineWindow& _other) = delete;
	GameEngineWindow& operator=(const GameEngineWindow&& _other) = delete;


public:	//Member Function Headers
	bool CreateMainWindowClass(HINSTANCE _hInstance, const std::string& _windowClassName);
	void CreateMainWindow(
		const std::string& _windowTitle,
		const float4& _windowPos,
		const float4& _windowSize
	);
	void SetWindowPosAndSize(const float4& _windowPos, const float4& _windowSize);
	void Update(void (*UpdateFunctions)());
	void TurnOffWindow();


public:	//Getter, Setter, Templated Member Functions
	static GameEngineWindow& GetInst()
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

	float4 GetWindowPos()
	{
		return windowPos_;
	}

	float4 GetWindowSize()
	{
		return windowSize_;
	}
};

