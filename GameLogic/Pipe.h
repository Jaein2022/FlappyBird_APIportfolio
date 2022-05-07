#pragma once

class Pipe: public GameEngineActor
{
	//Friend Classes


	//Member Variables


public:
	Pipe();
	~Pipe();

protected:
	Pipe(const Pipe& _other) = delete;
	Pipe(Pipe&& _other) noexcept = delete;

private:
	Pipe& operator=(const Pipe& _other) = delete;
	Pipe& operator=(const Pipe&& _other) = delete;


public:	//Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;
	void CheckCollision() override;


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

