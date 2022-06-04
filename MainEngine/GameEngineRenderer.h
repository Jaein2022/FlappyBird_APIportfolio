#pragma once

enum class RenderPivot
{
	Center,
	Bottom,
	LeftTop,
	MAX
};

class GameEngineActor;
class GameEngineImage;
class GameEngineRenderer: public GameEngineNameBase
{
	class Animation: public GameEngineNameBase
	{
		friend GameEngineRenderer;

		GameEngineRenderer* parentRenderer_;	//�� �ִϸ��̼��� ������ �θ� ������.
		int startIndex_;				//�ִϸ��̼� ���� �ε���.
		int finishIndex_;				//�ִϸ��̼� ���� �ε���.
		int curIndex_;					//���� �������� �ε���.
		float delayPerFrame_;			//�� �����Ӻ� �Ѿ�� �ð�.
		float curDelay_;				//���� �������� �Ѿ����� ���� �ð�.
		RenderPivot pivot_;				//���� �������� �̹��� �Ǻ�.
		bool isRepetitive_;				//�ִϸ��̼��� ���ѹݺ�/1ȸ�� ����.
		bool isFinished_;				//�ִϸ��̼��� �������� ����.


	private:
		Animation(GameEngineRenderer* _renderer)
			: parentRenderer_(_renderer),
			startIndex_(-1),
			finishIndex_(-1),
			curIndex_(-1),
			delayPerFrame_(-1.f),
			curDelay_(-1.f),
			pivot_(RenderPivot::MAX),
			isRepetitive_(true),
			isFinished_(true)
		{
			SetParent(_renderer);
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
	friend GameEngineActor;

	//Member Variables
	GameEngineActor* parentActor_;

	GameEngineImage* renderingImage_;	//Render() �Լ� ������ ���������� ������ �̹���.
	float4 renderingImagePos_;		//�̹��� ������ �������� ������ ������(���� ���).
	float4 renderingImageSize_;		//�̹������� �������� �� ũ��.
	float4 renderPivot_;	//�������ϴ� �̹����� ������. 
	//�� ���� �������� ���������� �ǹ������� �̹����� ��ġ�Ѵ�.

	float angle_;				//�������� ����.
	float4 renderSize_;			//�ڸ� �������̹����� ����� ���� �������� ũ��. �����ϸ� renderingImageSize_�� �����ϰ� �� ��.
	float4 localPos_;
	//���� ��ġ�� ��� ������ ���͸� ����ٴϴ� �������� ��ġ�Ҷ�, ��� �������� �󸶳� ������ ������ ��ġ���� ���ϴ� ����.
	//���� ��ġ���� ���� ����� �ʴ´ٸ� {0, 0}.

	GameEngineImage* maskImage_;

	Animation* curAnimation_;
	std::map<std::string, Animation*> allAnimations_;	//��� �ִϸ��̼��� ����.

	bool isCameraEffect_;

private:	
	GameEngineRenderer(GameEngineActor* _actor);
	~GameEngineRenderer();

protected:
	GameEngineRenderer(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;

private:
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete;


public:	//Member Function Headers
	void SetImage(const std::string& _imageName);
	void SetMaskImage(const std::string& _imageName);
	void Render();

	void SetRenderPivot(RenderPivot _pivot);


	void CreateAnimation(
		const std::string& _animationName,
		const std::string& _imageName,
		int _startIndex,
		int _finishIndex,
		float _delayPerFrame,
		bool _isRepetitive = true,
		RenderPivot _pivot = RenderPivot::Center
	);
	Animation* FindAnimation(const std::string& _animationName);
	void ChangeAnimation(const std::string& _animationName, bool _isForcedChange = false);
	void UpdateAnimation();
	void SetFrameIndex(int _index, RenderPivot _pivot);
	bool IsCurAnimationFinished();

public:	//Getter, Setter, Templated Member Functions
	GameEngineImage* const GetRenderingImage() const
	{
		return renderingImage_;
	}

	void SetRenderSize(const float4& _size)
	{
		renderSize_ = _size;
	}

	void SetLocalPos(const float4& _pos)
	{
		localPos_ = _pos;
	}

	float4 GetLocalPos()
	{
		return localPos_;
	}

	void Move(const float4& _distance)
	{
		localPos_ += _distance;
	}

	void SetRenderingImagePos(const float4& _pos = float4::Zero)
	{
		renderingImagePos_ = _pos;
	}

	void SetRenderingImageSize(const float4& _size)
	{
		renderingImageSize_ = _size;
	}

	void SetRenderPivot(const float4& _pos)
	{
		renderPivot_ = _pos;
	}

	void SetCameraEffectOn()
	{
		isCameraEffect_ = true;
	}

	void SetCameraEffectOff()
	{
		isCameraEffect_ = false;
	}

	GameEngineActor* const GetActor()
	{
		return parentActor_;
	}

	const std::string& GetCurAnimationName()
	{
		return curAnimation_->GetName();
	}

private://Member Function Headers

};

