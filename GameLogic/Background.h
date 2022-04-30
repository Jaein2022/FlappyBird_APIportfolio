#pragma once

class Background: public GameEngineActor
{
	//¹è°æ: ¹Ù´Ú, µÞ¹è°æ ·»´õ¸µ ´ã´ç.


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

