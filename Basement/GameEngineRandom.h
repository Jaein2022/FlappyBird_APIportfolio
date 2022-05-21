#pragma once

class GameEngineRandom
{
	std::mt19937_64 mt_;	//Mersenne Twister 유사난수 생성기.

	static GameEngineRandom* inst_;

private:
	GameEngineRandom() : mt_(
		std::chrono::system_clock::to_time_t(	
		//입력된 time_point구조체 형식의 시간을 time_t(==long long)형식으로 형변환하는 함수.
		std::chrono::system_clock::now()	//현재의 초단위 시간을 time_point구조체 형식으로 반환하는 함수.
		)
	)
	{
	}
	GameEngineRandom(__int64 _seed) : mt_(_seed)	//시드값 직접 입력.
	{
	}
	~GameEngineRandom()
	{
	}

protected:
	GameEngineRandom(const GameEngineRandom& _other) = delete;
	GameEngineRandom(GameEngineRandom&& _other) = delete;

private:
	GameEngineRandom& operator=(const GameEngineRandom& _other) = delete;
	GameEngineRandom& operator=(const GameEngineRandom&& _other) = delete;


public:
	static GameEngineRandom& GetInst()
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

	int GetRandomInt(int _min, int _max)
	{
		//대부분의 난수 알고리즘이 마지막 제한을 할때 %를 사용하므로 보통 _max -1까지 나온다는것을 항상 염두해 둘 것.
		std::uniform_int_distribution<int> intDistribution(_min, _max);
		return intDistribution(mt_);
	}

	float GetRandomFloat(float _min, float _max)
	{
		std::uniform_real_distribution<float> floatDistribution(_min, _max);
		return floatDistribution(mt_);
	}
};

