#pragma once

class GameEngineActor;
class GameEngineLevel: public GameEngineNameBase
{
	//Friend Classes
	friend class GameEngineLevelManager;

	//Member Variables

	std::map<std::string, GameEngineActor*> allActors_;					
	//�� ������ ���͵��� ������ ��.

	std::map<int, std::list<GameEngineActor*>> allActors_UpdateOrder_;	
	//�� ������ ���͵��� ������Ʈ ������� ������ ��.

	std::map<int, std::list<GameEngineActor*>> allActors_RenderOrder_;	
	//�� ������ ���͵��� ������ ������� ������ ��.

	float4 camPos_;			//ī�޶� ��ġ. 
	//����ٴϴ� �÷��̾��� �̵�����ŭ ���� ��ȭ�ϰ�, �� ��ȭ���� ī�޶��� ������ �޴� ���͵��� ������ �� ��ġ�� ����Ǽ�,
	//�÷��̾�� ��� �������� ��ǥ�� �ٲ����� ������ �������� ������ �ڸ��� ��� �������ǰ�
	//����� �������� �ʾ����� �÷��̾��� �ݴ�� �����ΰ�ó�� �������Ǿ�, 
	//��������� �÷��̾ ��� ���� �����̴� ��ó�� ���δ�.

	bool isLoaded_;

protected:
	GameEngineLevel();
	virtual ~GameEngineLevel();

protected:
	GameEngineLevel(const GameEngineLevel& _other) = delete;
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;

private:
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;


public:	//Member Function Headers.



public:	//Getter, Setter, Templated Member Functions.


protected:
	virtual void Load() = 0;		//�Ʒ� Initialize() �Լ��� ȣ���ϴ�, ���� ������ҵ��� �ҷ����� �Լ�.
	



protected:

	template<typename ActorType>
	void CreateActor(const std::string _actorName)
	{
		if (true == _actorName.empty())	//_actorName�� ���ٸ� ����.
		{
			GameEngineDebug::MsgBoxError("���� �̸��� �����ϴ�.");
			return;
		}

		std::map<int, std::list<GameEngineActor*>>::iterator it_Update = allActors_UpdateOrder_.find(0);
		if (allActors_UpdateOrder_.end() == it_Update)	//�⺻������ �־�� �� 0������Ʈ�� ���ٸ� ����.
		{
			GameEngineDebug::MsgBoxError("0�� ������Ʈ���� ����Ʈ�� �����ϴ�.");
			return;
		}

		std::map<int, std::list<GameEngineActor*>>::iterator it_Render = allActors_RenderOrder_.find(0);
		if (allActors_RenderOrder_.end() == it_Render)	//�⺻������ �־�� �� 0������Ʈ�� ���ٸ� ����.
		{
			GameEngineDebug::MsgBoxError("0�� �������� ����Ʈ�� �����ϴ�.");
			return;
		}


		ActorType* newActor = new ActorType();
		newActor->SetName(_actorName);
		newActor->SetParent(this);
		newActor->Initialize();

		//������ NewActor�� allActors �����̳ʵ鿡 �־ ���� ������� ����Ѵ�.
		allActors_.insert(std::map<std::string, GameEngineActor*>::value_type(_actorName, newActor));
		it_Update->second.push_back(newActor);
		it_Render->second.push_back(newActor);
	}


private://Member Function Headers.
	void Initialize();
	void Update();
	void Render();
	void SortUpdateOrder();			//������Ʈ ���� ���� �Լ�.
	void SortRenderOrder();			//������ ���� ���� �Լ�.
	//void RenderActors();
	//void RenderLevel();
};

