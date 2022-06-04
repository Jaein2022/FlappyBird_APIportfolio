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

		GameEngineRenderer* parentRenderer_;	//이 애니메이션을 생성한 부모 렌더러.
		int startIndex_;				//애니메이션 시작 인덱스.
		int finishIndex_;				//애니메이션 종료 인덱스.
		int curIndex_;					//현재 프레임의 인덱스.
		float delayPerFrame_;			//각 프레임별 넘어가는 시간.
		float curDelay_;				//현재 프레임이 넘어가기까지 남은 시간.
		RenderPivot pivot_;				//현재 프레임의 이미지 피봇.
		bool isRepetitive_;				//애니메이션이 무한반복/1회로 종료.
		bool isFinished_;				//애니메이션이 끝났는지 여부.


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

	GameEngineImage* renderingImage_;	//Render() 함수 내에서 최종적으로 렌더할 이미지.
	float4 renderingImagePos_;		//이미지 내에서 렌더링을 시작할 시작점(왼쪽 상단).
	float4 renderingImageSize_;		//이미지에서 렌더링을 할 크기.
	float4 renderPivot_;	//렌더링하는 이미지의 기준점. 
	//이 점을 기준으로 액터포스나 피벗포스에 이미지를 배치한다.

	float angle_;				//렌더러의 기울기.
	float4 renderSize_;			//자른 렌더링이미지를 백버퍼 위에 렌더링할 크기. 웬만하면 renderingImageSize_와 동일하게 할 것.
	float4 localPos_;
	//액터 위치를 벗어난 곳에서 액터를 따라다니는 렌더러를 배치할때, 어느 방향으로 얼마나 떨어진 지점에 배치할지 정하는 지점.
	//액터 위치에서 전혀 벗어나지 않는다면 {0, 0}.

	GameEngineImage* maskImage_;

	Animation* curAnimation_;
	std::map<std::string, Animation*> allAnimations_;	//모든 애니메이션을 저장.

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

