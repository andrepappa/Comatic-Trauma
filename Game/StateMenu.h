#pragma once

#include "PhoenixEngine/Core/GameState.h"

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
		AnimManager* Anims;
		//sf::Sprite* BgAnim;
		//sf::Sprite* StaticOverlay;
		//int BgAnimIndex;
		enum Menus
		{
			HOME,
			OPTIONS
		} CurrentMenu;
};