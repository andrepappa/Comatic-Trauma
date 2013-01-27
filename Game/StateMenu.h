#pragma once

#include "PhoenixEngine/Core/GameState.h"
#include "SoundController.h"
#include <SFML/Graphics.hpp>
#include "AnimManager.h"
class StateMenu : public GameState
{
	public:
		virtual void Init() override;
		virtual ~StateMenu();

		virtual void Update(sf::Time DeltaTime) override;
		virtual void HandleEvents(sf::Event EventHandle) override;
		virtual void Draw(sf::RenderWindow* Window) override;

	private:
		sf::Font _Font;
		sf::Text WiimoteConnectionStatus;
		AnimManager* Anims;
		sf::Sound MenuSound;
		sf::SoundBuffer MenuBuffer;
		sf::Sprite* Background;
		sf::Sprite* Highlight;
		bool Selected;
		bool WPressed;
		bool SPressed;
		bool UpPressed;
		bool DownPressed;
		enum Menus
		{
			HOME,
			OPTIONS
		} CurrentMenu;
};