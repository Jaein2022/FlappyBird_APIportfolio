#pragma once

class GameEngineTime
{
	static GameEngineTime* inst_;

	LARGE_INTEGER frequency_;		//�ʴ� CPU ���ļ�(�ʴ� Ŭ�� �ݺ� ȸ��). �������̹Ƿ� ó�� �ѹ��� ���.
	LARGE_INTEGER startCheck_;		//���� ���۽����� ���� Ŭ�� ��.
	LARGE_INTEGER endCheck_;		//���� ���������� ���� Ŭ�� ��.
	double deltaTime_;				//���� ������ �ѹ� ���� �� �� �ɸ� �ð� ==
	// ���� �ѹ��� �����Ǵ� Ŭ�� �� / �ʴ� CPU ���ļ�.
	//��ǻ���� ������ �������� ��ŸŸ�� ���� �۾����Ƿ�, ��ǻ�� ���� ������ ���� ���� �ٸ� �ӵ��� ������ �����Ѵٰ� �ص� 
	//���ɿ� �ݺ���ؼ� ��ŸŸ�� ���� �۰� ������, �׷� ���� ��ǻ�� ���� ������� ���� �ð� ���� ���� ����ӵ��� �����ְ� �ȴ�.

private:
	GameEngineTime();		//����Ʈ ������.
	~GameEngineTime();		//����Ʈ �Ҹ���.

public:
	GameEngineTime(const GameEngineTime& _other) = delete;		//����Ʈ ���������.
	GameEngineTime(GameEngineTime&& _other) = delete;		//����Ʈ rvalue ���������.

public:
	GameEngineTime& operator=(const GameEngineTime& _other) = delete;		//����Ʈ ���Կ�����.
	GameEngineTime& operator=(const GameEngineTime&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Reset();			//�ð� ���� �غ� �Լ�.
	void Update();			//��ŸŸ�� ���� �Լ�.

public:
	static GameEngineTime& GetInst()
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

	//��ȯ���� �⺻ �ڷ����̰� �ܼ��� �Լ���� ����� �����ص� �����ϴ�.
	double GetDeltaTimeD() const
	{
		return deltaTime_;
	}

	float GetDeltaTimeF() const
	{
		return static_cast<float>(deltaTime_);
	}
};

