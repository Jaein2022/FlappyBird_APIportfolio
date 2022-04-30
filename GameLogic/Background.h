#pragma once

class Background: public GameEngineActor
{
	//���: �ٴ�, �޹�� ������ ���.


	//Member Variables
	GameEngineRenderer* background_Renderer_;

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

public:	//Getter, Setter, Templated Member Functions

private://Member Function Headers
};

