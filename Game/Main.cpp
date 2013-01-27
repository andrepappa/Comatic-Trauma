#include "PhoenixEngine/Core/PhoenixEngine.h"

#include "StateLoading.h"
#include "StateMenu.h"
#include "LevelOne.h"
#include "Beat.h"
#include "SoundController.h"

#include "WiimoteBindings.h"

int main(int argc, char* argv[])
{
	PhoenixEngine* E = PhoenixEngine::GetInstance();
	E->DESIRED_FPS = 100;
	E->bVSYNC = true;
	E->WINDOW_TITLE = "Comatic Trauma";
	E->RESOLUTION = sf::Vector2u(1280, 720);
	//E->VID_FLAGS = sf::Style::Fullscreen;
	//E->SetLoadingState(new StateLoading);

	//	Beat BeatInstance;
	sf::Music* MyMusic = new sf::Music;
	MyMusic->openFromFile("Dox.ogg");
	MyMusic->setLoop(true);
	MyMusic->play();

	bool MenuOn = false;
	sf::Sound SelectSound;
	sf::SoundBuffer SelectBuffer;
	SelectBuffer.loadFromFile("Select.ogg");
	SelectSound.setBuffer(SelectBuffer);

	E->Init();
	
	E->QueueState(new StateMenu);
	while(E->Running())
	{
		E->Update();

		if (!MenuOn)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				MenuOn = true;
				SelectSound.play();
			}
		}

		E->Draw();
	}

	return 0;
}