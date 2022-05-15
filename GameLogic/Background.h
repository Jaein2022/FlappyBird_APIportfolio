#pragma once

class Background: public GameEngineActor
{
	//배경: 뒷배경 이동 배치 및 렌더링 담당.

	friend class GameEngineLevel;

	GameEngineRenderer* backgroundRenderer_;

private:
	Background();
	~Background();

protected:
	Background(const Background& _other) = delete;
	Background(Background&& _other) noexcept = delete;

private:
	Background& operator=(const Background& _other) = delete;
	Background& operator=(const Background&& _other) = delete;


public:	//Member Function Headers


public:	//Getter, Setter, Templated Member Functions


private://Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void CheckCollision() override;
};

