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
	sf::SoundBuffer MyBuffer2;
	sf::SoundBuffer MyBuffer3;
	sf::Sound BeatSound1;
	sf::Sound BeatSound2;
	sf::Sound BeatSound3;

private:
	CSoundController* SoundController;
	sf::Clock BeatTimer;
	sf::Clock DoubleBeat;
	float DoubleBeatTime;
	bool DoubleBeatSwitch;
};

