#pragma once

class UI: public GameEngineActor
{



	//Member Variables


public:
	UI();
	~UI();

protected:
	UI(const UI& _other) = delete;
	UI(UI&& _other) noexcept = delete;

private:
	UI& operator=(const UI& _other) = delete;
	UI& operator=(const UI&& _other) = delete;


public:	//Member Function Headers
	void Initialize() override;
	void Update() override;
	void Render() override;


public:	//Getter, Setter, Templated Member Functions



private://Member Function Headers


};

