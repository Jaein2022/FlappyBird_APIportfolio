#pragma once

class Background: public GameEngineActor
{
	//���: �޹�� �̵� ��ġ �� ������ ���.


	//Member Variables
	const int rendererCount_;
	const int widthInt_;;
	const float widthFloat_;
	float backgroundSpeed_;
	std::vector<GameEngineRenderer*> backgroundRenderers_;

	//��� �̹��� ũ��: 288 X 512 �ȼ�.

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

