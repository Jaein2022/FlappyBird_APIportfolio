#pragma once

class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor: public GameEngineNameBase
{
	//Friend Classes
	friend GameEngineLevel;

	//Member Variables
	GameEngineLevel* parentLevel_;

	std::map<std::string, GameEngineRenderer*> allRenderers_;
	float4 pos_;
	int renderOrder_;
	int updateOrder_;

protected:
	GameEngineActor();
	virtual ~GameEngineActor();

protected:
	GameEngineActor(const GameEngineActor& _other) = delete;
	GameEngineActor(GameEngineActor&& _other) noexcept = delete;

private:
	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete;


public:	//Member Function Headers
	void CreateRenderer(
		const std::string& _imageName,
		const std::string& _rendererName
	);
	float4 GetCamPos();


public:	//Getter, Setter, Templated Member Functions
	const float4 GetPos() const
	{
		return pos_;
	}
	void SetPos(const float4& _pos)		//액터의 위치를 특정 지점으로 재설정.
	{
		pos_ = _pos;
	}
	void Move(const float4& _direction)	//액터의 이동 방향과 속도 설정.
	{
		pos_ += _direction;
	}




protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	void SetRenderOrder(int _renderOrder)
	{
		renderOrder_ = _renderOrder;
	}
	void SetUpdateOrder(int _updateOrder)
	{
		updateOrder_ = _updateOrder;
	}


private://Member Function Headers


};

