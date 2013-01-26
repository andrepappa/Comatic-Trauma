#include "StateLoading.h"
#include "PhoenixEngine/Core/PhoenixEngine.h"
#include "PhoenixEngine/Core/Utility.h"

void StateLoading::Init()
{
	LoadBar = 0;
	Delay = 200;
	TextFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	TextObj.setFont(TextFont);
	TextObj.setCharacterSize(30);
	TextObj.setColor(sf::Color::White);

	TextObj.setString("Loading");
	TextObj.setPosition(Util::CenterText(&TextObj, PhoenixEngine::GetWindow()));

	Timer.restart();
}

StateLoading::~StateLoading()
{
}

void StateLoading::Update(sf::Time DeltaTime)
{
	if(Timer.getElapsedTime().asMilliseconds() >= Delay)
	{
		Timer.restart();
		LoadBar++;
		if(LoadBar > 3)
			LoadBar = 0;

		std::string LoadStr = "Loading";
		for(int i = 0; i < LoadBar; i++)
			LoadStr += ".";
		TextObj.setString(LoadStr);
	}
}

void StateLoading::HandleEvents(sf::Event EventHandle)
{
}

void StateLoading::Draw(sf::RenderWindow* Window)
{
	Window->draw(TextObj);
}