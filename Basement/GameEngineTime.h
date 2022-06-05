#pragma once

class GameEngineTime
{
	static GameEngineTime* inst_;

	//std::chrono::time_point: epoch라고 사전에 정해놓은, 특정 시점으로부터 
	// 사용자가 지정한 시점간의 시간 간격이 얼마나 되는지를 duration이라는 클래스로 표현하고 계산하는 클래스.

	//std::chrono::system_clock의 경우에는 유닉스 타임이라고 부르는 그레고리력 1970년 1월 1일 00시 00분 00초가 
	// epoch이며, 시스템 시간 설정에 따라서 시간이 역행해서 duration이 음수가 될 수도 있다.
	//std::chrono::steady_clock의 경우에는 시스템 부팅 시점이 epoch가 되며, 
	// 단방향(monotonic)으로만 시간이 흘러가므로 절대 역행하지 않고, duration이 음수가 나올 수도 없다.

	std::chrono::steady_clock::time_point prev_;


	double deltaTime_;		//지난 루프를 한번 수행 할 때 걸린 시간 ==
	// 루프 한번당 누적되는 클럭 수 / 초당 CPU 주파수.
	//컴퓨터의 성능이 좋을수록 델타타임 값이 작아지므로, 컴퓨터 성능 격차로 인해 각자 다른 속도로 루프를 수행한다고 해도 
	//성능에 반비례해서 델타타임 값이 작게 잡히고, 그로 인해 컴퓨터 성능 상관없이 같은 시간 같은 게임 진행속도를 보여주게 된다.

private:
	GameEngineTime();		//디폴트 생성자.
	~GameEngineTime();		//디폴트 소멸자.

public:
	GameEngineTime(const GameEngineTime& _other) = delete;		//디폴트 복사생성자.
	GameEngineTime(GameEngineTime&& _other) = delete;		//디폴트 rvalue 복사생성자.

public:
	GameEngineTime& operator=(const GameEngineTime& _other) = delete;		//디폴트 대입연산자.
	GameEngineTime& operator=(const GameEngineTime&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Reset();			//시간 측정 준비 함수.
	void Update();			//델타타임 갱신 함수.

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

	//반환값이 기본 자료형이고 단순한 함수라면 헤더에 구현해도 무방하다.
	double GetDeltaTimeD() const
	{
		return deltaTime_;
	}

	float GetDeltaTimeF() const
	{
		return static_cast<float>(deltaTime_);
	}
};

