#pragma once

class Background: public GameEngineActor
{
	//배경: 뒷배경 이동 배치 및 렌더링 담당.


	//Member Variables
	const int rendererCount_;
	const float width_;
	float speed_;
	std::vector<GameEngineRenderer*> backgroundRenderers_;

	//배경 이미지 크기: 288 X 512 픽셀.

public:
	Background();
	~Background();

protected:
	Background(const Background& _other) = delete;
	Background(Background&& _other) noexcept = delete;

private:
	Background& operator=(const Background& _other) = delete;
	Background& operator=(const Background&& _other) = delete;


public:	//Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void CheckCollision() override;

public:	//Getter, Setter, Templated Member Functions
	void SetSpeed(float _speed)
	{
		speed_ = _speed;
	}

private://Member Function Headers
};

