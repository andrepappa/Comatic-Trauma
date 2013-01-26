#include "Obstacle.h"


Obstacle::Obstacle()
{
}


Obstacle::~Obstacle() {}


void Obstacle::Update(sf::Time DeltaTime)
{

}

void Obstacle::HandleEvents(sf::Event EventHandle)
{

}

void Obstacle::Draw(sf::RenderWindow* Window)
{
	Window->draw(*m_GOSprite);
}