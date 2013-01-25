#include "WiimoteBindings.h"

#include "wiiyourself/wiimote.h"
#include "PhoenixEngine/Core/Utility.h"
#include <SFML/System.hpp>

wiimote WiimoteBindings::Wiimote;
int WiimoteBindings::Timeout = 2000;

bool WiimoteBindings::connectWiimote()
{
	int TimeoutCount = 0;
	while(!Wiimote.Connect(wiimote::FIRST_AVAILABLE))
	{
		Util::msgNote("Looking for Wiimote...");
		sf::sleep(sf::milliseconds(500));
		TimeoutCount += 500;
		if(TimeoutCount > Timeout)
		{
			Util::msgErr("Could not find connectible Wiimote");
			return false;
		}
	}

	Wiimote.SetLEDs(0x0f);
	return true;
}

bool WiimoteBindings::isDown(WiimoteKeys Key)
{
	return false;
}