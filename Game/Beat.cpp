#include "Beat.h"
#include <iostream>


Beat::Beat()
{
	SoundController = new CSoundController();
	BeatTimer.restart();
	DoubleBeat.restart();
	DoubleBeatTime = 82.0f;
	DoubleBeatSwitch = false;
	MyBuffer.loadFromFile("Beat.wav");
	BeatSound1.setBuffer(MyBuffer);
	BeatSound2.setBuffer(MyBuffer);
}


Beat::~Beat()
{
}

void Beat::Update()
{
	if (DoubleBeat.getElapsedTime().asMilliseconds() >= DoubleBeatTime+1050)
	{
		BeatSound1.play();
		BeatTimer.restart();
		DoubleBeat.restart();
		DoubleBeatSwitch = false;
	}
	if (BeatTimer.getElapsedTime().asMilliseconds() >= 1000)
	{
		// 82 milliseconds long to play + code time
		BeatSound1.play();
		BeatTimer.restart();
	}
}