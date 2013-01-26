#include "PhoenixEngine/Core/PhoenixEngine.h"

#include "StateTest.h"
#include "LevelOne.h"

#include "WiimoteBindings.h"
int main(int argc, char* argv[])
{
	PhoenixEngine* E = PhoenixEngine::GetInstance();
	E->DESIRED_FPS = 60;
	E->WINDOW_TITLE = "Comatic Trauma!111!!111!1!!1oneone";
	E->RESOLUTION = sf::Vector2u(1280, 720);
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