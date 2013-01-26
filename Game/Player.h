#pragma once
#include "gameobject.h"
#include <iostream>

#include <SFML\Graphics.hpp>
class Player :
	public GameObject
{
public:
	Player();
	~Player();

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

	void CollidedWith(Collision* Other);

	void SetCamera(sf::View* Cam){ Camera = Cam; }

private:
	float PosX;
	float PosY;
	float Speed;
	float DirectionX;
	float DirectionY;
	float JumpDefault;
	float JumpReduce;
	float JumpSpeed;
	bool Jumping;
	bool Falling;
	sf::Time m_DeltaTime;
	sf::View* Camera;
	sf::FloatRect CameraBounds;
};

