#pragma once
#include "gameobject.h"
#include "AnimManager.h"


class Fragment :
	public GameObject
{
public:
	Fragment();
	~Fragment();

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

	void setPosition(float x, float y);

private:
	AnimManager* FragAnim;
	sf::Sprite* FragSprite;
	std::vector<sf::Texture*> FragTexture;
	int FragIndex;


};

