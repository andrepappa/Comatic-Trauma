#pragma once
#include "gameobject.h"
#include "Collision.h"
#include <SFML\Graphics.hpp>

class Background :
	public GameObject
{
public:
	Background();
	~Background();
	
	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;
	
	void SetCamera(sf::View* Cam){ Camera = Cam; }
	// void SetPlayerPos(float x, float y); // Set the position so we know where the player is and can change the background based on that?

private:
	sf::View* Camera;

	class ParallaxImage
	{
		public:
			sf::Sprite* Sprites[2];
			sf::Vector2f Direction;
	};

	std::vector<ParallaxImage*> m_Backgrounds;
};

