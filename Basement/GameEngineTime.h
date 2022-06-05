#pragma once

class GameEngineTime
{
	static GameEngineTime* inst_;

	//std::chrono::time_point: epoch��� ������ ���س���, Ư�� �������κ��� 
	// ����ڰ� ������ �������� �ð� ������ �󸶳� �Ǵ����� duration�̶�� Ŭ������ ǥ���ϰ� ����ϴ� Ŭ����.

	//std::chrono::system_clock�� ��쿡�� ���н� Ÿ���̶�� �θ��� �׷����� 1970�� 1�� 1�� 00�� 00�� 00�ʰ� 
	// epoch�̸�, �ý��� �ð� ������ ���� �ð��� �����ؼ� duration�� ������ �� ���� �ִ�.
	//std::chrono::steady_clock�� ��쿡�� �ý��� ���� ������ epoch�� �Ǹ�, 
	// �ܹ���(monotonic)���θ� �ð��� �귯���Ƿ� ���� �������� �ʰ�, duration�� ������ ���� ���� ����.

	std::chrono::steady_clock::time_point prev_;


	double deltaTime_;		//���� ������ �ѹ� ���� �� �� �ɸ� �ð� ==
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

