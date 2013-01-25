#include "PhoenixEngine/Core/PhoenixEngine.h"

#include "StateTest.h"
#include "LevelOne.h"

#include "WiimoteBindings.h"
int main(int argc, char* argv[])
{
	PhoenixEngine* E = PhoenixEngine::GetInstance();
	E->DESIRED_FPS = 60;
	E->WINDOW_TITLE = "Phoenix Engine Test";
	E->RESOLUTION = sf::Vector2u(800, 800);
	//E->SetLoadingState(new SOMETHING);
	E->Init();
	
	E->QueueState(new StateTest);
	//WiimoteBindings::connectWiimote();
	while(E->Running())
	{
		E->Update();
		E->Draw();
	}

	return 0;
}