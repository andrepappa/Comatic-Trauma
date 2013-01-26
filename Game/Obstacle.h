#pragma once
#include "gameobject.h"
#include "PhoenixEngine\Core\ImageManager.h"

class Obstacle :
	public GameObject
{

public:
	Obstacle();
	~Obstacle();

	virtual void Update(sf::Time DeltaTime);
	virtual void HandleEvents(sf::Event EventHandle);
	virtual void Draw(sf::RenderWindow* Window);

	void setSprite(sf::Sprite* S){ m_GOSprite = S; }

};

