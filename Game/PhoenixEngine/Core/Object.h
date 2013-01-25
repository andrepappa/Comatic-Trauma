#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Object
{
	public:
		virtual void Update(sf::Time DeltaTime) = 0;
		virtual void HandleEvents(sf::Event EventHandle) = 0;
		virtual void Draw() = 0;
		virtual ~Object(){};
};