#include <SFML/Graphics.hpp>
#include "LevelOne.h"
#include "StateTest.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"


LevelOne::~LevelOne() {}


void LevelOne::Init()
{

}

void LevelOne::Update(sf::Time DeltaTime)
{

}

void LevelOne::HandleEvents(sf::Event EventHandle)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		PhoenixEngine::GetInstance()->QueueState(new StateTest);
		std::cout << "In Level1"; // jumping jacks
		
	}

}

void LevelOne::Draw()
{


}
