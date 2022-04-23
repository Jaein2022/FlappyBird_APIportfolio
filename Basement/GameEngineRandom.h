#pragma once

class GameEngineRandom
{
	std::mt19937_64 mt_;	//Mersenne Twister 유사난수 생성기.


public:
	GameEngineRandom() : mt_()	//자체 시드값 사용.
	{
		std::random_device rng;
		mt_.seed(rng());		//<-???
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
	int RandomInt(int _min, int _max)
	{
		//보통 대부분의 난수 알고리즘이 마지막 제한을 할때 %를 사용하므로 
		//보통 _max -1까지 나온다는것을 항상 염두해 둘 것.
		std::uniform_int_distribution<int> intDistribution(_min, _max);
		return intDistribution(mt_);
	}

	float RandomFloat(float _min, float _max)
	{
		std::uniform_real_distribution<float> floatDistribution(_min, _max);
		return floatDistribution(mt_);
	}
};

