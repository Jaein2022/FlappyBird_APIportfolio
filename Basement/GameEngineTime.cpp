#include "PreCompile.h"
#include "GameEngineTime.h"

GameEngineTime* GameEngineTime::inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime() : deltaTime_(0.000)
{
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	prev_ = std::chrono::steady_clock::now();
	Update();
}

void GameEngineTime::Update()
{
	std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
	//이번 루프의 시작시간을 time_point형으로 저장한다.

	//std::chrono::duration<Rep, Period = std::ratio<1>>: 특정 길이의 시간 간격이 몇 틱인지, 
	// Rep에 넣어준 형식으로 저장하는 클래스.
	//틱간 간격은 Period / 1초 간격이고, 아무 값도 넣어주지 않으면 기본값인 std::ratio<1>이 입력되어 초당 1틱으로 설정된다. 

	//std::ratio<Num, Denom = 1>: Num / Denom의 형태로 입력받은 분수나 비율을 표현, 계산하는 클래스. 

	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(current - prev_);
	//이번 루프의 시작시간 - 지난 루프의 시작시간 = 지난 루프를 수행하는데 걸린 시간 == 델타타임.
	//델타타임을 duration<double>형태로 저장한다.

	deltaTime_ = time_span.count();
	//duration<double>형태로 저장된 델타타임이 몇 틱인지 계산한다. 
	// 두번째 타입에 아무 값도 넣어주지 않았으므로 초당 1틱으로 계산된다.
	//std::chrono::duration<Rep, Period>::count(): duration형식의 변수에 저장된 시간이 몇 틱인지 반환하는 함수. 

	prev_ = current;
}