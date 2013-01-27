
#include "Beat.h"
#include <iostream>

#include "WiimoteBindings.h"
Beat::Beat()
{
	SoundController = new CSoundController();
	BeatTimer.restart();
	DoubleBeat.restart();
	DoubleBeatTime = 82.0f;
	DoubleBeatSwitch = false;
	MyBuffer.loadFromFile("Beat.wav");
	MyBuffer2.loadFromFile("Beep.ogg");
	MyBuffer3.loadFromFile("Flatline.ogg");
	BeatSound1.setBuffer(MyBuffer);
	BeatSound2.setBuffer(MyBuffer2);
	BeatSound3.setBuffer(MyBuffer3);
}


Beat::~Beat()
{
}

void Beat::Update()
{
	if (DoubleBeat.getElapsedTime().asMilliseconds() >= DoubleBeatTime+1050)
	{
		WiimoteBindings::setRumble(50);
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
		WiimoteBindings::setRumble(50);
	}
}