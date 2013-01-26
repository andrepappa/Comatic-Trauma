#pragma once

#include "PhoenixEngine/Core/GameState.h"

#include <SFML/Graphics.hpp>
class StateLoading : public GameState
{
	public:
		virtual void Init() override;
		virtual ~StateLoading();

		virtual void Update(sf::Time DeltaTime) override;
		virtual void HandleEvents(sf::Event EventHandle) override;
		virtual void Draw(sf::RenderWindow* Window) override;

	private:
		sf::Font TextFont;
		sf::Text TextObj;
		int LoadBar;
		sf::Clock Timer;
		int Delay;
};