#pragma once

#include <SFML\Graphics.hpp>
#include "PhoenixEngine\Core\ImageManager.h"
#include "PhoenixEngine\Core\Utility.h"

#include <iostream>
#include <cmath>

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
			{
				sf::IntRect SpriteRect(0,0,0,0), SpriteRectOther(0,0,0,0);
				SpriteRect.left = CollisionRef->getPosition().x;
				SpriteRect.top = CollisionRef->getPosition().y;
				SpriteRect.width = CollisionRef->getTextureRect().width;
				SpriteRect.height = CollisionRef->getTextureRect().height;
				SpriteRectOther.left = Other->CollisionRef->getPosition().x;
				SpriteRectOther.top = Other->CollisionRef->getPosition().y;
				SpriteRectOther.width = Other->CollisionRef->getTextureRect().width;
				SpriteRectOther.height = Other->CollisionRef->getTextureRect().height;

				Intersects = SpriteRect.intersects(SpriteRectOther, IntersectingRect);
			}
			else
				return false;

			if(!Intersects)
				return false;
			
			sf::Vector2i BaggaOFF21(IntersectingRect.left - CollisionRef->getPosition().x, IntersectingRect.top - CollisionRef->getPosition().y);
			sf::Vector2i BaggaOFF2(IntersectingRect.left - Other->CollisionRef->getPosition().x, IntersectingRect.top - Other->CollisionRef->getPosition().y);

			bool** CData = ImageManager::RequestCollisionData(CollisionRef->getTexture());
			bool** OtherCData = ImageManager::RequestCollisionData(Other->CollisionRef->getTexture());

			for(int x = 0; x < IntersectingRect.width-1; x++)
			{
				for(int y = 0; y < IntersectingRect.height-1; y++)
				{
					if(CData[x+BaggaOFF21.x][y+BaggaOFF21.y] && OtherCData[x+BaggaOFF2.x][y+BaggaOFF2.y])
					{
						CollidedWith(Other);
						Other->CollidedWith(this);
						return true;
					}
				}
				//Util::msgNote("");
			}

			return false;
		}

		virtual void CollidedWith(Collision* Other)
		{
		}
};
