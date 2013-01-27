#include "WiimoteBindings.h"

#include "wiiyourself/wiimote.h"
#include "wiiyourself/wiimote_state.h"
#include "PhoenixEngine/Core/Utility.h"
#include <SFML/System.hpp>

wiimote WiimoteBindings::Wiimote;
int WiimoteBindings::Timeout = 10000;
std::map<WiimoteKeys, bool> WiimoteBindings::KeyPressedStates;
std::map<WiimoteKeys, bool> WiimoteBindings::KeyReleasedStates;

bool WiimoteBindings::connectWiimote()
{
	if(Wiimote.IsConnected())
		Wiimote.Disconnect();
	Wiimote.ChangedCallback = nullptr;
	Wiimote.CallbackTriggerFlags = (state_change_flags)(CONNECTED);
	int TimeoutCount = 0;

	/* Reset all key states */
	for(int i = (int)(WiimoteKeys::NONE); i < (int)(WiimoteKeys::COUNT); i++)
	{
		KeyPressedStates[(WiimoteKeys)i] = false;
		KeyReleasedStates[(WiimoteKeys)i] = false;
	}

	/* Look for controller */
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

	Util::msgNote("Wiimote connected!");
	WiimoteBindings::setLEDs(true, false, false, false);
	return true;
}

void WiimoteBindings::playSample(wiimote_sample Snd)
{
	if(!Wiimote.IsConnected())
		return;
	if(Wiimote.ConnectionLost())
		connectWiimote();

	Wiimote.EnableSpeaker(true);
	Wiimote.MuteSpeaker(false);
	Wiimote.PlaySample(Snd);
}

bool WiimoteBindings::isDown(WiimoteKeys Key)
{
	if(!Wiimote.IsConnected())
		return false;
	if(Wiimote.ConnectionLost())
		connectWiimote();

	Wiimote.RefreshState();
	
	switch(Key)
	{
		case LEFT:
			return Wiimote.Button.Left();
		case UP:
			return Wiimote.Button.Up();
		case RIGHT:
			return Wiimote.Button.Right();
		case DOWN:
			return Wiimote.Button.Down();
		case A:
			return Wiimote.Button.A();
		case B:
			return Wiimote.Button.B();
		case ONE:
			return Wiimote.Button.One();
		case TWO:
			return Wiimote.Button.Two();
		case PLUS:
			return Wiimote.Button.Plus();
		case MINUS:
			return Wiimote.Button.Minus();
		case HOME:
			return Wiimote.Button.Home();
		default:
			return false;
	}
}

bool WiimoteBindings::isPressed(WiimoteKeys Key)
{
	if(!Wiimote.IsConnected())
		return false;
	if(Wiimote.ConnectionLost())
		connectWiimote();
	
	bool ret = false;
	bool bPressed = isDown(Key);
	if(bPressed && !KeyPressedStates[Key])
		ret = true;

	KeyPressedStates[Key] = bPressed;
	return ret;
}

bool WiimoteBindings::isReleased(WiimoteKeys Key)
{
	if(!Wiimote.IsConnected())
		return false;
	if(Wiimote.ConnectionLost())
		connectWiimote();

	bool ret = false;
	bool bPressed = isDown(Key);
	if(!bPressed && !KeyReleasedStates[Key])
		ret = true;

	KeyReleasedStates[Key] = !bPressed;
	return ret;
}

WORD WiimoteBindings::getAllPressed()
{
	if(!Wiimote.IsConnected())
		return false;
	if(Wiimote.ConnectionLost())
		connectWiimote();
	
	return Wiimote.Button.Bits;
}

void WiimoteBindings::setLEDs(bool LED1, bool LED2, bool LED3, bool LED4)
{
	if(!Wiimote.IsConnected())
		return;
	if(Wiimote.ConnectionLost())
		connectWiimote();

	short bits = (LED1 ? 1 : 0) + (LED2 ? 2 : 0) + (LED3 ? 4 : 0) + (LED4 ? 8 : 0);

	std::cout << "Bits: " << bits << "\n";
	Wiimote.SetLEDs(bits);
}

void WiimoteBindings::setRumble(unsigned int ms)
{
	if(!Wiimote.IsConnected())
		return;
	if(Wiimote.ConnectionLost())
		connectWiimote();

	Wiimote.RumbleForAsync(ms);
}