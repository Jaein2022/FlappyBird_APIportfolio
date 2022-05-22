#pragma once

class Background: public GameEngineActor
{
	//배경: 뒷배경 이동 배치 및 렌더링 담당.

	friend class GameEngineLevel;

	GameEngineRenderer* background_Renderer_;

private:
	Background();
	~Background();

protected:
	Background(const Background& _other) = delete;
	Background(Background&& _other) noexcept = delete;

private:
	Background& operator=(const Background& _other) = delete;
	Background& operator=(const Background&& _other) = delete;


public:	


public:	


private:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) override;
};

