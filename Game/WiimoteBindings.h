#pragma once

#include "wiiyourself/wiimote.h"
#include <map>
enum WiimoteKeys
{
	NONE = 0x0,
	LEFT,
	UP,
	RIGHT,
	DOWN,
	A,
	B,
	ONE,
	TWO,
	PLUS,
	MINUS,
	HOME,
	COUNT /* Size of WiimoteKeys */
};

class WiimoteBindings
{
	public:
		static void setConnectionTimeout(int T){ Timeout = T; }
		static bool connectWiimote();
		static bool connected(){ return Wiimote.IsConnected(); }
		static bool isDown(WiimoteKeys Key);		//Held down
		static bool isPressed(WiimoteKeys Key);		//Pressed event
		static bool isReleased(WiimoteKeys Key);	//Released event
		static void playSample(wiimote_sample Snd); //Play sound
		static WORD getAllPressed();				//Get all as bit mask
		static void setLEDs(bool LED1, bool LED2, bool LED3, bool LED4);
		static void setRumble(unsigned int ms);

	private:
		static wiimote Wiimote;
		static int Timeout;
		static std::map<WiimoteKeys, bool> KeyPressedStates, KeyReleasedStates;
};