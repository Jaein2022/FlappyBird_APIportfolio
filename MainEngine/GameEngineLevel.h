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

	float4 cameraPos_;			//ī�޶� ��ġ. 
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
	float4 GetCameraPos()
	{
		return cameraPos_;
	}
	void SetCameraPos(const float4& _pos)
	{
		cameraPos_ = _pos;
	}

	void MoveCamera(const float4& _direction)
	{
		cameraPos_ += _direction;
	}

protected:
	virtual void Load() = 0;		//�Ʒ� Initialize() �Լ��� ȣ���ϴ�, ���� ������ҵ��� �ҷ����� �Լ�.
	



protected:

	template<typename ActorType>
	void CreateActor(const std::string& _actorName, int _updateOrder = 0, int _renderOrder = 0)
	{
		if (true == _actorName.empty())	//_actorName�� ���ٸ� ����.
		{
			GameEngineDebug::MsgBoxError("���� �̸��� �����ϴ�.");
			return;
		}

		ActorType* newActor = new ActorType(this);
		newActor->SetName(_actorName);
		newActor->SetParent(this);
		newActor->Initialize();

		//������ NewActor�� allActors �����̳ʵ鿡 �־ ���� ������� ����Ѵ�.
		allActors_.insert(std::map<std::string, GameEngineActor*>::value_type(_actorName, newActor));
		allActors_UpdateOrder_[_updateOrder].push_back(newActor);
		allActors_RenderOrder_[_renderOrder].push_back(newActor);
	}


private:	//Member Function Headers.
	void Initialize();
	void Update();
	void Render();
	void SortUpdateOrder();			//������Ʈ ���� ���� �Լ�.
	void SortRenderOrder();			//������ ���� ���� �Լ�.
};

