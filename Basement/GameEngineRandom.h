#pragma once

class GameEngineRandom
{
	std::mt19937_64 mt_;	//Mersenne Twister ���糭�� ������.


public:
	GameEngineRandom() : mt_()	//��ü �õ尪 ���.
	{
		std::random_device rng;
		mt_.seed(rng());		//<-???
	}
	GameEngineRandom(__int64 _seed) : mt_(_seed)	//�õ尪 ���� �Է�.
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
		//���� ��κ��� ���� �˰����� ������ ������ �Ҷ� %�� ����ϹǷ� 
		//���� _max -1���� ���´ٴ°��� �׻� ������ �� ��.
		std::uniform_int_distribution<int> intDistribution(_min, _max);
		return intDistribution(mt_);
	}

	float RandomFloat(float _min, float _max)
	{
		std::uniform_real_distribution<float> floatDistribution(_min, _max);
		return floatDistribution(mt_);
	}
};

