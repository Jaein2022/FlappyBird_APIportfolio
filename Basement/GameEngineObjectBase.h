#pragma once

class GameEngineObjectBase
{
	//���� �� ��� ������Ʈ�� �⺻ ���(������Ʈ ���� ����, ����� ����) ��� Ŭ����. 
	 
	//Member Variables
	bool isDead_;					//true == ��� ����. ���ó���� �ƴ� ��� �����ӿ� ����.
	bool isUpdateOn_;				//false == ������Ʈ ���� ����.
	bool isDebugChecked_;			//true == �ش� ������Ʈ�� ����� üũ�� ��.

	GameEngineObjectBase* parentObject_;	//�θ� ������Ʈ.


public:
	GameEngineObjectBase();
	virtual ~GameEngineObjectBase();
	//�θ� Ŭ������ �Ҹ��ڰ� �����Լ��� ���� ������ �ڽ� Ŭ������ �Ҹ��ڰ� ȣ����� �ʴ´�.
	//��ü���� ������ ������ ���߿� ������ ��.

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
			//�θ� ������Ʈ�� �ڱ� �ڽ� ���� �ϳ��� isDead_�� true��� ��� ����.
		}
	}

	bool IsUpdateOn()
	{
		if (nullptr == parentObject_)
		{
			return isUpdateOn_ && (false == isDead_);
			//�θ� ������Ʈ�� ���ٸ� �ڱ� �ڽ��� ��������鼭 ������Ʈ���� ���ܵ��� �ʾҴٸ� true ��ȯ.
		}
		else
		{
			return (false == isDead_) &&		//�ڱ� �ڽ��� ��������鼭,
				(true == this->isUpdateOn_) && 	//������Ʈ���� ���ܵ��� �ʰ�,
				(true == parentObject_->isUpdateOn_);
			//�θ� ������Ʈ���� ���ܵ��� �ʾҴٴ� ���ǵ��� ��� �޼��ؾ� true ��ȯ.
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

	void SwitchUpdateOnOff()
	{
		isUpdateOn_ = !isUpdateOn_;
	}

	void CheckDebug()
	{
		isDebugChecked_ = true;
	}

	GameEngineObjectBase* GetParent()
	{
		return parentObject_;
	}

	void SetParent(GameEngineObjectBase* _parent)
	{
		parentObject_ = _parent;
	}

};
