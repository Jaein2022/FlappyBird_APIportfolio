#pragma once

class PipeAndBase: public GameEngineActor
{
	//Friend Classes


	//Member Variables


public:
	PipeAndBase();
	~PipeAndBase();

protected:
	PipeAndBase(const PipeAndBase& _other) = delete;
	PipeAndBase(PipeAndBase&& _other) noexcept = delete;

private:
	PipeAndBase& operator=(const PipeAndBase& _other) = delete;
	PipeAndBase& operator=(const PipeAndBase&& _other) = delete;


public:	//Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void CheckCollision() override;


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

