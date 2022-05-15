#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollisionBody.h"

GameEngineLevel::GameEngineLevel(): cameraPos_(float4::ZERO), isLoaded_(false)
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator iter = allActors_UpdateOrder_.begin();
		iter != allActors_UpdateOrder_.end(); iter++)
	{
		iter->second.clear();
	}
	allActors_UpdateOrder_.clear();

	for (std::map<int, std::list<GameEngineActor*>>::iterator iter = allActors_RenderOrder_.begin();
		iter != allActors_RenderOrder_.end(); iter++)
	{
		iter->second.clear();
	}
	allActors_RenderOrder_.clear();

	for (std::map<std::string, GameEngineActor*>::iterator iter = allActors_.begin();
		iter != allActors_.end(); iter++)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	allActors_.clear();
}




void GameEngineLevel::Initialize()
{
	if (true == isLoaded_)
	{
		GameEngineDebug::MsgBoxError("������ �̹� �غ�Ǿ��ֽ��ϴ�.");
		return;
	}
	else
	{
		Load();
		isLoaded_ = true;
	}
}

void GameEngineLevel::Update()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_UpdateOrder_.begin();
		mapIter != allActors_UpdateOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); listIter++)
		{
			(*listIter)->Update();
		}
	}
}

void GameEngineLevel::Render()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_RenderOrder_.begin();
		mapIter != allActors_RenderOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); listIter++)
		{
			(*listIter)->Render();
		}
	}
}

void GameEngineLevel::SortUpdateOrder()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_UpdateOrder_.begin();
		mapIter != allActors_UpdateOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); listIter++)
		{
			if (mapIter->first == (*listIter)->updateOrder_)
			{
				continue;	//������ �´ٸ� ���.
			}

			//������ �ȸ´ٸ� ���⼱ �ϴ� ���Ը�.
			if (allActors_UpdateOrder_.end() == allActors_UpdateOrder_.find((*listIter)->updateOrder_))
			{
				allActors_UpdateOrder_.insert(
					std::map<int, std::list<GameEngineActor*>>::value_type(
						(*listIter)->updateOrder_, std::list<GameEngineActor*>()));
			}

			std::map<int, std::list<GameEngineActor*>>::iterator mapIter_inserted = 
				allActors_UpdateOrder_.find((*listIter)->updateOrder_);

			mapIter_inserted->second.push_back((*listIter));
		}
	}

	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_UpdateOrder_.begin();
		mapIter != allActors_UpdateOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); )
		{
			if (mapIter->first == (*listIter)->updateOrder_)
			{
				++listIter;
				continue;	//������ �´ٸ� listIter�� �������� �ѱ�� ���.
			}

			//������ Ʋ�� ���� �����.
			listIter = mapIter->second.erase(listIter);
		}
	}
}

void GameEngineLevel::SortRenderOrder()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_RenderOrder_.begin();
		mapIter != allActors_RenderOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); listIter++)
		{
			if (mapIter->first == (*listIter)->renderOrder_)
			{
				continue;	//������ �´ٸ� ���.
			}

			//������ �ȸ¾Ƶ� ���⼱ �ϴ� ���Ը�.
			if (allActors_RenderOrder_.end() == allActors_RenderOrder_.find((*listIter)->renderOrder_))
			{
				allActors_RenderOrder_.insert(
					std::map<int, std::list<GameEngineActor*>>::value_type(
						(*listIter)->renderOrder_, std::list<GameEngineActor*>()));
			}
			std::map<int, std::list<GameEngineActor*>>::iterator mapIter_inserted = 
				allActors_RenderOrder_.find((*listIter)->renderOrder_);

			mapIter_inserted->second.push_back((*listIter));

		}
	}

	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_RenderOrder_.begin();
		mapIter != allActors_RenderOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); )
		{
			if (mapIter->first == (*listIter)->renderOrder_)
			{
				++listIter;
				continue;	//������ �´ٸ� listIter�� �ڷ� �ѱ�� ���.
			}

			//������ Ʋ�� ���� �����.
			listIter = mapIter->second.erase(listIter);
		}
	}
}

void GameEngineLevel::ReleaseDeadActor()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_UpdateOrder_.begin();
		mapIter != allActors_UpdateOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end();)
		{
			if (true == (*listIter)->IsDead())
			{
				listIter = mapIter->second.erase(listIter);
			}
			else
			{
				++listIter;
			}
		}
	}

	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIter = allActors_RenderOrder_.begin();
		mapIter != allActors_RenderOrder_.end(); mapIter++)
	{
		for (std::list<GameEngineActor*>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); )
		{
			if (true == (*listIter)->IsDead())
			{
				listIter = mapIter->second.erase(listIter);
			}
			else
			{
				++listIter;
			}
		}
	}

	for (std::map<std::string, GameEngineActor*>::iterator iter = allActors_.begin();
		iter != allActors_.end(); )
	{
		if (true == iter->second->IsDead())
		{
			delete iter->second;
			iter->second = nullptr;
			iter = allActors_.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

