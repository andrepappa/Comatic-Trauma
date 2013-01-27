#include "PhoenixEngine/Core/PhoenixEngine.h"

#include "StateLoading.h"
#include "StateMenu.h"
#include "LevelOne.h"
#include "Beat.h"

#include "WiimoteBindings.h"

int main(int argc, char* argv[])
{
	PhoenixEngine* E = PhoenixEngine::GetInstance();
	E->DESIRED_FPS = 100;
	E->bVSYNC = true;
	E->WINDOW_TITLE = "Comatic Trauma!111!!111!1!!1oneone";
	E->RESOLUTION = sf::Vector2u(1280, 720);
	//E->VID_FLAGS = sf::Style::Fullscreen;
	//E->SetLoadingState(new StateLoading);

//	Beat BeatInstance;

	E->Init();
	
	E->QueueState(new StateMenu);
	while(E->Running())
	{
		E->Update();

		E->Draw();
	}

	return 0;

}