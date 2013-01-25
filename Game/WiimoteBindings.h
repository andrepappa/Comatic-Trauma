#pragma once

#include "wiiyourself/wiimote.h"
enum WiimoteKeys
{
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
	HOME
};

class WiimoteBindings
{
	public:
		static void setConnectionTimeout(int T){ Timeout = T; }
		static bool connectWiimote();
		static bool isDown(WiimoteKeys Key);
	private:
		static wiimote Wiimote;
		static int Timeout;
};