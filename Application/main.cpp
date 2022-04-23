#include "PreCompile.h"

#include <conio.h>
int main()
{
	GameEngineSoundManager::GetInst().Initialize();

	//while (true)
	//{
	//	_getch();
	//}




	GameEngineSoundManager::Destroy();
}