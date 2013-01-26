#pragma once
#include "gameobject.h"
#include "AnimManager.h"


class Enemies :
	public GameObject
{
public:
	Enemies();
	~Enemies();

	void Update(sf::Time DeltaTime);
	void Draw(sf::RenderWindow* window);
	void HandleEvents(sf::Event EventHandle);

	void setSprite(sf::Sprite* S){ m_GOSprite = S; }

private:
	AnimManager* AnimMgr;
	int Anim_Idle, Anim_Run, Anim_Jump, Anim_Fall;

	float Speed;
	sf::Vector2f target;
};

