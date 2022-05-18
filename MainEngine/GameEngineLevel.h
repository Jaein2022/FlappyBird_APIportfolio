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
	//각 레벨별 액터들을 저장한 맵.

	std::map<int, std::list<GameEngineActor*>> allActors_UpdateOrder_;	
	//각 레벨별 액터들을 업데이트 순서대로 정리한 맵.

	std::map<int, std::list<GameEngineActor*>> allActors_RenderOrder_;	
	//각 레벨별 액터들을 렌더링 순서대로 정리한 맵.

	float4 cameraPos_;			//카메라 위치. 
	//따라다니는 플레이어의 이동량만큼 같이 변화하고, 그 변화량이 카메라의 영향을 받는 액터들의 윈도우 내 위치에 역산되서,
	//플레이어는 계속 움직여서 좌표가 바뀌지만 윈도우 내에서는 고정된 자리에 계속 렌더링되고
	//배경은 움직이지 않았지만 플레이어의 반대로 움직인것처럼 렌더링되어, 
	//결과적으로 플레이어가 배경 위를 움직이는 것처럼 보인다.

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
	virtual void Load() = 0;		//아래 Initialize() 함수가 호출하는, 레벨 구성요소들을 불러오는 함수.
	virtual void UpdateLevel() = 0;

protected:
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _actorName, int _updateOrder = 0, int _renderOrder = 0)
	{
		if (true == _actorName.empty())	//_actorName이 없다면 폭파.
		{
			GameEngineDebug::MsgBoxError("액터 이름이 없습니다.");
			return nullptr;
		}

		ActorType* newActor = new ActorType();
		newActor->SetName(_actorName);
		newActor->SetParent(this);
		newActor->parentLevel_ = this;
		newActor->Initialize();

		//생성한 NewActor를 allActors 컨테이너들에 넣어서 관리 대상으로 등록한다.
		allActors_UpdateOrder_[_updateOrder].push_back(newActor);
		allActors_RenderOrder_[_renderOrder].push_back(newActor);

		std::pair<std::map<std::string, GameEngineActor*>::iterator, bool> insertResult = allActors_.insert(
				std::map<std::string, GameEngineActor*>::value_type(
					_actorName, newActor
				)
		);

		if (false == insertResult.second)
		{
			GameEngineDebug::MsgBoxError(insertResult.first->first + ": 같은 이름의 액터가 이미 존재합니다.");
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
	void SortUpdateOrder();			//업데이트 순서 정렬 함수.
	void SortRenderOrder();			//렌더링 순서 정렬 함수.
	void ReleaseDeadActor();		//삭제된 액터를 제거하는 함수.
};

