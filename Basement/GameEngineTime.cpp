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
	//�̹� ������ ���۽ð��� time_point������ �����Ѵ�.

	//std::chrono::duration<Rep, Period = std::ratio<1>>: Ư�� ������ �ð� ������ �� ƽ����, 
	// Rep�� �־��� �������� �����ϴ� Ŭ����.
	//ƽ�� ������ Period / 1�� �����̰�, �ƹ� ���� �־����� ������ �⺻���� std::ratio<1>�� �ԷµǾ� �ʴ� 1ƽ���� �����ȴ�. 

	//std::ratio<Num, Denom = 1>: Num / Denom�� ���·� �Է¹��� �м��� ������ ǥ��, ����ϴ� Ŭ����. 

	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(current - prev_);
	//�̹� ������ ���۽ð� - ���� ������ ���۽ð� = ���� ������ �����ϴµ� �ɸ� �ð� == ��ŸŸ��.
	//��ŸŸ���� duration<double>���·� �����Ѵ�.

	deltaTime_ = time_span.count();
	//duration<double>���·� ����� ��ŸŸ���� �� ƽ���� ����Ѵ�. 
	// �ι�° Ÿ�Կ� �ƹ� ���� �־����� �ʾ����Ƿ� �ʴ� 1ƽ���� ���ȴ�.
	//std::chrono::duration<Rep, Period>::count(): duration������ ������ ����� �ð��� �� ƽ���� ��ȯ�ϴ� �Լ�. 

	prev_ = current;
}