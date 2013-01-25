#pragma once

#include "PhoenixEngine/Core/GameState.h"
#include <iostream>

class StateTest : public GameState
{
	public:
		virtual void Init() override;
		virtual ~StateTest();

		virtual void Update(sf::Time DeltaTime) override;
		virtual void HandleEvents(sf::Event EventHandle) override;
		virtual void Draw(sf::RenderWindow* Window) override;
};