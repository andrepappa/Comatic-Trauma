#pragma once

#include <SFML\Graphics.hpp>

class Collision
{
	public:
		Collision()
		{
			CollisionRef = nullptr;
		}

		sf::Sprite* CollisionRef;

		bool CheckCollision(Collision* Other)
		{
			sf::Rect<int> IntersectingRect;
			bool Intersects = false;
			if(CollisionRef != nullptr && Other->CollisionRef != nullptr)
				Intersects = CollisionRef->getTextureRect().intersects(Other->CollisionRef->getTextureRect(), IntersectingRect);
			else
				return false;

			if(!Intersects)
				return false;

			for(int x = 0; x < IntersectingRect.width; x++)
			{
				for(int y = 0; y < IntersectingRect.height; y++)
				{
					//If Pixel at (x, y) and
					//if other Pixel at (x, y)
					//per-pixel collision

				}
			}

			return false;
		}

		virtual void CollidedWith(Collision* Other)
		{
		}
};

