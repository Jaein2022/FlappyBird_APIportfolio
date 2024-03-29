#pragma once
#include "LogicEnum.h"

class PlayLevel;
class UI: public GameEngineActor
{
	friend class GameEngineLevel;

	PlayLevel* parentPlayLevel_;
	GameEngineRenderer* readyMessage_Renderer_;	//�� ���ӿ��� �����ϰ� �길 �����Ǻ��� �ٴ�.
	const float4 numberSize_;
	GameEngineRenderer* score_FirstDigit_Renderer_;
	GameEngineRenderer* score_SecondDigit_Renderer_;
	GameEngineRenderer* gameover_Renderer_;

private: 
	UI();
	~UI();

protected:
	UI(const UI& _other) = delete;
	UI(UI&& _other) noexcept = delete;

private:
	UI& operator=(const UI& _other) = delete;
	UI& operator=(const UI&& _other) = delete;


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

