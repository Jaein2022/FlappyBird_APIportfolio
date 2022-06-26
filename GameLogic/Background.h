#pragma once

class Background: public GameEngineActor
{
	//¹è°æ: µÞ¹è°æ ·»´õ¸µ ´ã´ç.

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


private:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void ReactCollision(
		GameEngineCollisionBody* _thisCollisionBody,
		GameEngineActor* _other,
		GameEngineCollisionBody* _otherCollisionBody
	) override;

private:


};

