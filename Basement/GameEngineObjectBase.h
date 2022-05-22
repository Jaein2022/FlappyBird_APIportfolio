#pragma once

class GameEngineObjectBase
{
	//게임 내 모든 오브젝트의 기본 기능(업데이트 제외 여부, 디버깅 보조) 담당 클래스. 
	 
	//Member Variables
	bool isDead_;					//true == 사망 판정. 사망처리가 아닌 사망 판정임에 주의.
	bool isInUpdate_;				//false == 업데이트 제외 판정.
	bool isDebugChecked_;			//true == 해당 오브젝트만 디버그 체크를 함.

	GameEngineObjectBase* parentObject_;	//부모 오브젝트.


public:
	GameEngineObjectBase();
	virtual ~GameEngineObjectBase();
	//부모 클래스의 소멸자가 가상함수가 되지 않으면 자식 클래스의 소멸자가 호출되지 않는다.
	//구체적인 이유나 원리는 나중에 공부할 것.

protected:
	GameEngineObjectBase(const GameEngineObjectBase& _other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept = delete;

private:
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete;



public:	//Getter, Setter, Templated Member Functions
	bool IsNull()
	{
		return nullptr == this;
	}

	bool IsDead()
	{
		if (nullptr == parentObject_)
		{
			return isDead_;
		}
		else
		{
			return true == (this->isDead_ || parentObject_->isDead_);
			//부모 오브젝트와 자기 자신 둘중 하나라도 isDead_가 true라면 사망 판정.
		}
	}

	bool IsInUpdate()
	{
		if (nullptr == parentObject_)
		{
			return isInUpdate_ && (false == isDead_);
			//부모 오브젝트가 없다면 자기 자신이 살아있으면서 업데이트에서 제외되지 않았다면 true 반환.
		}
		else
		{
			return (false == isDead_) &&		//자기 자신이 살아있으면서,
				(true == this->isInUpdate_) && 	//업데이트에서 제외되지 않고,
				(true == parentObject_->isInUpdate_);
			//부모도 업데이트에서 제외되지 않았다는 조건들을 모두 달성해야 true 반환.
		}
	}

	bool IsDebugChecked()
	{
		if (true == isDebugChecked_)
		{
			int i = 0;
			i++;
		}
		return isDebugChecked_;
	}

	void Die()
	{
		isDead_ = true;
	}

	void ExcludeUpdate()
	{
		isInUpdate_ = false;
	}

	void IncludeUpdate()
	{
		isInUpdate_ = true;
	}

	void CheckDebug()
	{
		isDebugChecked_ = true;
	}

	GameEngineObjectBase* GetParent()
	{
		return parentObject_;
	}

protected:
	void SetParent(GameEngineObjectBase* _parent)
	{
		parentObject_ = _parent;
	}

};

