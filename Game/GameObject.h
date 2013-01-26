#pragma once

#include "phoenixengine\core\object.h"
#include "Collision.h"


class GameObject :
	public Object, public Collision
{
public:
	virtual void Update(sf::Time DeltaTime) = 0;
	virtual void HandleEvents(sf::Event EventHandle) = 0;
	virtual void Draw(sf::RenderWindow* Window) = 0;

protected:
	sf::Sprite* m_GOSprite;

};

