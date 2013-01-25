#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class GameState : public Object
{
	public:
		virtual void Init() = 0;
		virtual ~GameState(){};
};