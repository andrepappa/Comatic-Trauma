#include "StateMenu.h"
#include "LevelOne.h"
#include "PhoenixEngine/Core/PhoenixEngine.h"
#include "PhoenixEngine/Core/ImageManager.h"
void StateMenu::Init()
{
	Anims = new AnimManager;
	std::vector<sf::IntRect*> Rects = Anims->GetSubRects(1280, 720, 60, 8, 0, 0);
	Background = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Front.png"));
	Background->setPosition(0, 0);
	Highlight = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/High_light_START.png"));
	Highlight->setPosition(30, 200);
	Selected = 0;
	WPressed = false;
	SPressed = false;
	UpPressed = false;
	DownPressed = false;
}

StateMenu::~StateMenu()
{
}

void StateMenu::Update(sf::Time DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!WPressed && !SPressed && !UpPressed && !DownPressed)
		{
			Selected = !Selected;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			WPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			SPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			UpPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			DownPressed = true;
		}
	}
	if (Selected == 0)
	{
		Highlight->setTexture(*ImageManager::RequestTexture("Assets/GraphicalAssets/High_light_START.png"));
		Highlight->setPosition(52.0f, 455.0);
	}
	else
	{
		Highlight->setTexture(*ImageManager::RequestTexture("Assets/GraphicalAssets/High_light_QUIT.png"));
		Highlight->setPosition(58.5f, 553.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (Selected == 0)
		{
			PhoenixEngine::QueueState(new LevelOne);
		}
		else
		{
			PhoenixEngine::GetInstance()->Quit();
		}
	}
}

void StateMenu::HandleEvents(sf::Event EventHandle)
{
	if (EventHandle.type == sf::Event::KeyReleased && EventHandle.key.code == sf::Keyboard::W)
	{
		WPressed = false;
	}
	if (EventHandle.type == sf::Event::KeyReleased && EventHandle.key.code == sf::Keyboard::S)
	{
		SPressed = false;
	}
	if (EventHandle.type == sf::Event::KeyReleased && EventHandle.key.code == sf::Keyboard::Up)
	{
		UpPressed = false;
	}
	if (EventHandle.type == sf::Event::KeyReleased && EventHandle.key.code == sf::Keyboard::Down)
	{
		DownPressed = false;
	}
}

void StateMenu::Draw(sf::RenderWindow* Window)
{
	Window->setView(Window->getDefaultView());
	Window->draw(*Background);
	Window->draw(*Highlight);
}