#include "PhoenixEngine/Core/PhoenixEngine.h"

#include "StateLoading.h"
#include "StateMenu.h"

#include "WiimoteBindings.h"
int main(int argc, char* argv[])
{
	PhoenixEngine* E = PhoenixEngine::GetInstance();
	E->DESIRED_FPS = 60;
	E->WINDOW_TITLE = "Comatic Trauma!111!!111!1!!1oneone";
	E->RESOLUTION = sf::Vector2u(1280, 720);
	E->SetLoadingState(new StateLoading);
	E->Init();
	
	E->QueueState(new StateMenu);
	while(E->Running())
	{
		E->Update();
		E->Draw();
	}

	return 0;
}