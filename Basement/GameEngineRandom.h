#pragma once

class GameEngineRandom
{
	std::mt19937_64 mt_;	//Mersenne Twister ���糭�� ������.

	static GameEngineRandom* inst_;

private:
	GameEngineRandom() : mt_(
		std::chrono::system_clock::to_time_t(	
		//�Էµ� time_point����ü ������ �ð��� time_t(==long long)�������� ����ȯ�ϴ� �Լ�.
		std::chrono::system_clock::now()	//������ �ʴ��� �ð��� time_point����ü �������� ��ȯ�ϴ� �Լ�.
		)
	)
	{
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
		//��κ��� ���� �˰����� ������ ������ �Ҷ� %�� ����ϹǷ� ���� _max -1���� ���´ٴ°��� �׻� ������ �� ��.
		std::uniform_int_distribution<int> intDistribution(_min, _max);
		return intDistribution(mt_);
	}

	float GetRandomFloat(float _min, float _max)
	{
		std::uniform_real_distribution<float> floatDistribution(_min, _max);
		return floatDistribution(mt_);
	}
};

