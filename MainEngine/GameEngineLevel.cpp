#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel(): camPos_(float4::ZERO), isLoaded_(false)
{
	//0�� ����Ʈ�� �⺻������ ����, ������ ���´�.
	allActors_RenderOrder_.insert(
		std::map<int, std::list<GameEngineActor*>>::value_type(
			0, std::list<GameEngineActor*>()));

	allActors_UpdateOrder_.insert(
		std::map<int, std::list<GameEngineActor*>>::value_type(
			0, std::list<GameEngineActor*>()));
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator it = allActors_UpdateOrder_.begin();
		it != allActors_UpdateOrder_.end(); ++it)
	{
		it->second.clear();
	}
	allActors_UpdateOrder_.clear();

	for (std::map<int, std::list<GameEngineActor*>>::iterator it = allActors_RenderOrder_.begin();
		it != allActors_RenderOrder_.end(); ++it)
	{
		it->second.clear();
	}
	allActors_RenderOrder_.clear();

	for (std::map<std::string, GameEngineActor*>::iterator it = allActors_.begin();
		it != allActors_.end(); ++it)
	{
		if (nullptr != it->second)
		{
			delete it->second;
			it->second = nullptr;
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
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIt = allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<GameEngineActor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			(*listIt)->Update();
		}
	}
}

void GameEngineLevel::Render()
{
	//RenderActors();
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<GameEngineActor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			(*listIt)->Render();
		}
	}


	//RenderLevel();
}

void GameEngineLevel::SortUpdateOrder()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIt = allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<GameEngineActor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			if (mapIt->first == (*listIt)->updateOrder_)
			{
				continue;	//������ �´ٸ� ���.
			}

			//������ �ȸ´ٸ� ���⼱ �ϴ� ���Ը�.
			if (allActors_UpdateOrder_.end() == allActors_UpdateOrder_.find((*listIt)->updateOrder_))
			{
				allActors_UpdateOrder_.insert(
					std::map<int, std::list<GameEngineActor*>>::value_type(
						(*listIt)->updateOrder_, std::list<GameEngineActor*>()));
			}

			std::map<int, std::list<GameEngineActor*>>::iterator mapIt_inserted = 
				allActors_UpdateOrder_.find((*listIt)->updateOrder_);

			mapIt_inserted->second.push_back((*listIt));
		}
	}

	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIt = allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<GameEngineActor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); )
		{
			if (mapIt->first == (*listIt)->updateOrder_)
			{
				++listIt;
				continue;	//������ �´ٸ� listIt�� �������� �ѱ�� ���.
			}

			//������ Ʋ�� ���� �����.
			listIt = mapIt->second.erase(listIt);
		}
	}
}

void GameEngineLevel::SortRenderOrder()
{
	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<GameEngineActor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			if (mapIt->first == (*listIt)->renderOrder_)
			{
				continue;	//������ �´ٸ� ���.
			}

			//������ �ȸ¾Ƶ� ���⼱ �ϴ� ���Ը�.
			if (allActors_RenderOrder_.end() == allActors_RenderOrder_.find((*listIt)->renderOrder_))
			{
				allActors_RenderOrder_.insert(
					std::map<int, std::list<GameEngineActor*>>::value_type(
						(*listIt)->renderOrder_, std::list<GameEngineActor*>()));
			}
			std::map<int, std::list<GameEngineActor*>>::iterator mapIt_inserted = 
				allActors_RenderOrder_.find((*listIt)->renderOrder_);

			mapIt_inserted->second.push_back((*listIt));

		}
	}

	for (std::map<int, std::list<GameEngineActor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<GameEngineActor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); )
		{
			if (mapIt->first == (*listIt)->renderOrder_)
			{
				++listIt;
				continue;	//������ �´ٸ� listIt�� �ڷ� �ѱ�� ���.
			}

			//������ Ʋ�� ���� �����.
			listIt = mapIt->second.erase(listIt);
		}
	}
}

//void GameEngineLevel::RenderActors()
//{
//}

//void GameEngineLevel::RenderLevel()
//{
//}
