#pragma once

#include "phoenixengine\core\gamestate.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include "AnimManager.h"
#include "HeartBeatMonitor.h"
#include "Fragment.h"

class LevelOne :
	public GameState
{
public:
	virtual ~LevelOne(void);
	virtual void Init() override;

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

private:
	Player* ThePlayer;
	sf::Clock HealthTimer;
	sf::Time HealthTimerInterval;
	std::vector<GameObject*> m_LOObjects;
	sf::View* Camera;
	AnimManager* Anims;
	sf::Sprite* BgAnim;
	sf::Sprite* StaticOverlay;
	int BgAnimIndex;
	std::vector<sf::Texture*> m_SmokeBorder;
	sf::Sprite* m_SmokeSprite;
	HeartBeatMonitor* Heartmon;
	Fragment* RanFrag;

};


