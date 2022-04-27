#pragma once

enum class RenderPivot
{
	CENTER,
	BOT,
	LEFTTOP,
	MAX
};

class GameEngineImage;
class GameEngineRenderer: public GameEngineNameBase
{
	class Animation
	{
		friend GameEngineRenderer;

		int startIndex_;				//�ִϸ��̼� ���� �ε���.
		int finishIndex_;				//�ִϸ��̼� ���� �ε���.
		int curIndex_;					//���� �������� �ε���.
		float delayPerFrame_;			//�� �����Ӻ� �Ѿ�� �ð�.
		float curDelay_;				//���� �������� �Ѿ����� ���� �ð�.
		GameEngineRenderer* parentRenderer_;	//�� �ִϸ��̼��� ������ �θ� ������.
		GameEngineImage* animationImage_;		//�ִϸ��̼��� �����ϴ� �߷��� �̹���.
		RenderPivot pivot_;				//���� �������� �̹��� �Ǻ�.
		bool isRepetitive_;				//�ִϸ��̼��� ���ѹݺ�/1ȸ�� ����.
		bool isFinished_;				//�ִϸ��̼��� �������� ����.


	private:
		Animation()
			: startIndex_(-1),
			finishIndex_(-1),
			curIndex_(-1),
			delayPerFrame_(-1.f),
			curDelay_(-1.f),
			parentRenderer_(nullptr),
			animationImage_(nullptr),
			pivot_(RenderPivot::MAX),
			isRepetitive_(true),
			isFinished_(true)
		{
		}

		void Reset()
		{
			curIndex_ = startIndex_;
			curDelay_ = delayPerFrame_;
			isFinished_ = false;
		}

		void Update();
	};



	//Friend Classes
	friend class GameEngineActor;

	//Member Variables

	float4 renderSize_;			//�ڸ� �����̹����� ����� ���� �������� ũ��. �����ϸ� actorImageSize_�� �����ϰ� �� ��.
	float4 rendererLocalPosition_;
	//���� ��ġ�� ��� ������ ���͸� ����ٴϴ� �������� ��ġ�Ҷ�, ��� �������� �󸶳� ������ ������ ��ġ���� ���ϴ� ����.
	//���� ��ġ���� ���� ����� �ʴ´ٸ� {0, 0}.

	GameEngineImage* actorImage_;	
	float4 actorImagePos_;		//�����̹��� ������ �������� ������ ������(���� ���).
	float4 actorImageSize_;		//�����̹������� �������� �� ũ��.
	float4 actorImagePivot_;	//�������ϴ� �̹����� ������. 
	//�� ���� �������� ���������� �ǹ������� �̹����� ��ġ�Ѵ�.

	GameEngineImage* maskImage_;

	Animation* curAnimation_;
	std::map<std::string, Animation*> allAnimations_;	//��� �ִϸ��̼��� ����.


public:
	GameEngineRenderer();
	~GameEngineRenderer();

protected:
	GameEngineRenderer(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;

private:
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete;


public:	//Member Function Headers
	void SetActorImage(const std::string& _imageName);
	void SetMaskImage(const std::string& _maskName);
	void Render();

public:	//Getter, Setter, Templated Member Functions


private://Member Function Headers
	
	void SetActorImagePivot(RenderPivot _pivot);

	void CreateAnimation(
		const std::string& _animationName,
		const std::string& _imageName,
		int _startIndex,
		int _finishIndex,
		float _delayPerFrame,
		bool isRepetitive_ = true,
		RenderPivot _pivot = RenderPivot::BOT
	);

};

