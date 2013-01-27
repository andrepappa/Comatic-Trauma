#pragma once

#include <SFML/System/Clock.hpp>
#include "SoundController.h"

class Beat
{
public:
	Beat();
	~Beat();

	void Update();
	sf::SoundBuffer MyBuffer;
	sf::Sound BeatSound1;
	sf::Sound BeatSound2;

private:
	CSoundController* SoundController;
	sf::Clock BeatTimer;
	sf::Clock DoubleBeat;
	float DoubleBeatTime;
	bool DoubleBeatSwitch;
};

