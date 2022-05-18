#pragma once

class GameEngineCollisionBody;
class GameEngineActor;
class GameEngineLevel: public GameEngineNameBase
{
	//Friend Classes
	friend GameEngineCollisionBody;
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
	virtual void UpdateLevel() = 0;

protected:
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _actorName, int _updateOrder = 0, int _renderOrder = 0)
	{
		if (true == _actorName.empty())	//_actorName�� ���ٸ� ����.
		{
			GameEngineDebug::MsgBoxError("���� �̸��� �����ϴ�.");
			return nullptr;
		}

		ActorType* newActor = new ActorType();
		newActor->SetName(_actorName);
		newActor->SetParent(this);
		newActor->parentLevel_ = this;
		newActor->Initialize();

		//������ NewActor�� allActors �����̳ʵ鿡 �־ ���� ������� ����Ѵ�.
		allActors_UpdateOrder_[_updateOrder].push_back(newActor);
		allActors_RenderOrder_[_renderOrder].push_back(newActor);

		std::pair<std::map<std::string, GameEngineActor*>::iterator, bool> insertResult = allActors_.insert(
				std::map<std::string, GameEngineActor*>::value_type(
					_actorName, newActor
				)
		);

		if (false == insertResult.second)
		{
			GameEngineDebug::MsgBoxError(insertResult.first->first + ": ���� �̸��� ���Ͱ� �̹� �����մϴ�.");
			return nullptr;
		}

		return newActor;
	}

	GameEngineActor* FindActor(const std::string& _actorName)
	{
		std::map<std::string, GameEngineActor*>::iterator findIter = allActors_.find(_actorName);
		if (allActors_.end() == findIter)
		{
			return nullptr;
		}
		else
		{
			return findIter->second;
		}
	}


private:	//Member Function Headers.
	void Initialize();
	void Update();
	void Render();
	void CheckCollision();
	void SortUpdateOrder();			//������Ʈ ���� ���� �Լ�.
	void SortRenderOrder();			//������ ���� ���� �Լ�.
	void ReleaseDeadActor();		//������ ���͸� �����ϴ� �Լ�.
};

