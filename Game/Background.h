#pragma once
#include "gameobject.h"
#include "Collision.h"
#include <SFML\Graphics.hpp>

class Background :
	public GameObject,
	public Collision
{
public:
	Background();
	~Background();
	
	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;
	
	void SetCamera(sf::View* Cam){ Camera = Cam; }

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

