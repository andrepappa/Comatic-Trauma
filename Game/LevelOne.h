#pragma once

#include "phoenixengine\core\gamestate.h"
#include <iostream>


class LevelOne :
	public GameState
{
public:
	virtual ~LevelOne(void);
	virtual void Init() override;

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

};

