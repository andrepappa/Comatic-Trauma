#include "StateTest.h"

#include "PhoenixEngine/Core/PhoenixEngine.h"
#include "LevelOne.h"
#include <SFML/Graphics.hpp>

sf::Font StateTest_Font;
sf::Text StateTest_Text1, StateTest_Text2;

#include "WiimoteBindings.h"

#include "PhoenixEngine/Core/Utility.h"

void StateTest::Init()
{
	StateTest_Font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	StateTest_Text1.setFont(StateTest_Font);
	StateTest_Text2.setFont(StateTest_Font);
	StateTest_Text1.setCharacterSize(50);
	StateTest_Text2.setCharacterSize(20);
	StateTest_Text1.setColor(sf::Color::White);
	StateTest_Text2.setColor(sf::Color::White);

	StateTest_Text1.setString("Hallå Där");
	StateTest_Text2.setString("Projektet fungerar");
	StateTest_Text1.setPosition(300, 300);
	StateTest_Text2.setPosition(320, 350);
}

StateTest::~StateTest()
{

}

void StateTest::Update(sf::Time DeltaTime)
{
	if(WiimoteBindings::isPressed(WiimoteKeys::ONE))
		Util::msgNote("ONE PRESSED!");
	if(WiimoteBindings::isDown(WiimoteKeys::ONE))
		Util::msgNote("ONE DOWN!");
	if(WiimoteBindings::isReleased(WiimoteKeys::ONE))
		Util::msgNote("ONE RELEASED!");

	static bool T1 = false, T2 = false, T3 = false, T4 = false;
	if(WiimoteBindings::isPressed(WiimoteKeys::UP))
	{
		T1 = !T1;
		WiimoteBindings::setLEDs(T1, T2, T3, T4);
	}
	if(WiimoteBindings::isPressed(WiimoteKeys::RIGHT))
	{
		T2 = !T2;
		WiimoteBindings::setLEDs(T1, T2, T3, T4);
	}
	if(WiimoteBindings::isPressed(WiimoteKeys::DOWN))
	{
		T3 = !T3;
		WiimoteBindings::setLEDs(T1, T2, T3, T4);
	}
	if(WiimoteBindings::isPressed(WiimoteKeys::LEFT))
	{
		T4 = !T4;
		WiimoteBindings::setLEDs(T1, T2, T3, T4);
	}

	if(WiimoteBindings::isPressed(WiimoteKeys::B))
		WiimoteBindings::setRumble(100);
}

void StateTest::HandleEvents(sf::Event EventHandle)
{

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
			PhoenixEngine::GetInstance()->QueueState(new LevelOne);
			std::cout << "test";
	}

}

void StateTest::Draw(sf::RenderWindow* Window)
{
	Window->draw(StateTest_Text1);
	Window->draw(StateTest_Text2);
}