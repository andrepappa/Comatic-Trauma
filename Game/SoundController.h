#pragma once

#include "PhoenixEngine/Core/PhoenixEngine.h"
#include <SFML/Audio.hpp>
#include <string>

class CSoundController
{
public:
	CSoundController();
	~CSoundController();

	sf::SoundBuffer applyFilter(float val, std::string path);
	void PlayChosenSound(std::string path);
	void Update();

private:
	float val;
	bool playTrigger;
	sf::Time offSet;
	float dovReduce;
	unsigned int musicCounter;
	sf::Music* MyMusic;
	sf::Sound* MySound;
	sf::SoundBuffer MyBuffer;
	sf::SoundBuffer* firstBuffer;
	sf::Sound* targetTemp;
	const sf::SoundBuffer* tempBuffer;
};

