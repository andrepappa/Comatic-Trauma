#pragma once

#include "phoenixengine\core\gamestate.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include "AnimManager.h"
#include "Enemies.h"


class LevelTest :
	public GameState
{
public:
	virtual ~LevelTest(void);
	virtual void Init() override;

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

protected:
	std::vector<GameObject*> m_LOObjects;
	sf::View* Camera;

};

