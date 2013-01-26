#include "SoundController.h"
#include <iostream>


CSoundController::CSoundController()
{
	MySound = new sf::Sound;
	firstBuffer = new sf::SoundBuffer;
	targetTemp = new sf::Sound;
	tempBuffer = new sf::SoundBuffer;
	// Code for applying the low pass filter when initiated
	/*
	playTrigger = false;
	musicCounter = 0;
	val = 0.80f;
	dovReduce = 0.05f;
	MyBuffer = applyFilter(val, "Dox.ogg");
	MySound->setBuffer(MyBuffer);
	MySound->play();
	*/
}

CSoundController::~CSoundController()
{
}

sf::SoundBuffer CSoundController::applyFilter(float val, std::string path)
{
	sf::SoundBuffer* firstBuffer = new sf::SoundBuffer;
	sf::Sound* targetTemp = new sf::Sound();
	const sf::SoundBuffer* tempBuffer;
	firstBuffer->loadFromFile(path);
	targetTemp->setBuffer(*firstBuffer);
	tempBuffer = targetTemp->getBuffer();

	// Get the source buffer
	const sf::Int16* drySamples = tempBuffer->getSamples();

	int numSamples = targetTemp->getBuffer()->getSampleCount();
	int channels = targetTemp->getBuffer()->getChannelCount();
	int sampleRate = targetTemp->getBuffer()->getSampleRate();

	// Copy and modify the samples
	std::vector<sf::Int16> wetSamples;
	wetSamples.reserve(numSamples);

	float b = 1.0f - val;
	float z = 0;

	for (int n = 0; n < numSamples; n++)
	{
		z = (drySamples[n] * b) + (z * val);
		wetSamples.push_back(z);
	}

	// Load the modified samples
	sf::SoundBuffer TempBuffer;
	TempBuffer.loadFromSamples(&wetSamples[0], wetSamples.size(), channels, sampleRate);
	
	return TempBuffer;
}

void CSoundController::Update()
{
	// Code for applying the low pass filter real time
	/*
	offSet = MySound->getPlayingOffset();
	//MySound->stop();
	sf::Clock funkyTime;
	funkyTime.restart();
	MyBuffer = applyFilter(val, "Dox.ogg");
	MySound->setBuffer(MyBuffer);
	MySound->setPlayingOffset(offSet+funkyTime.getElapsedTime());
	MySound->play();
	playTrigger = false;
	*/
}

void CSoundController::PlaySound(std::string path)
{
	sf::Sound MySound;
	sf::SoundBuffer MyBuffer;
	MyBuffer.loadFromFile(path);
	MySound.setBuffer(MyBuffer);
	MySound.play();
	std::cout << "Play Actual Sound" << std::endl;
}