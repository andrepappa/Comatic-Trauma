#pragma once
#include "gameobject.h"
#include "AnimManager.h"

#include "Player.h"
class Enemies :
	public GameObject
{
public:
	Enemies();
	~Enemies();

	void Update(sf::Time DeltaTime);
	void Draw(sf::RenderWindow* window);
	void HandleEvents(sf::Event EventHandle);

	void setPosition(sf::Vector2f Pos){ m_GOSprite->setPosition(Pos); } 
	void setPlayer(Player* P){ PlayerTarget = P; }

	bool CheckCollision(Collision* Other, bool bNotify /* = true */)
	{
		Player* P = dynamic_cast<Player*>(Other);
		if(P == NULL)
			return false;
	}

private:
	AnimManager* AnimMgr;
	int EnemyAnim;
	bool bLastDirWasLeft;
	Player* PlayerTarget;

	float Speed;
	sf::Clock ReTargetTimer;
	sf::Time ReTargetDelay;
	sf::Vector2f target;
};

