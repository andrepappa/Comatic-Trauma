#pragma once
#include "gameobject.h"
#include <iostream>

#include <SFML\Graphics.hpp>
#include "AnimManager.h"

class Player :
	public GameObject
{
	public:
		Player();
		~Player();

		virtual void Update(sf::Time DeltaTime) override;
		virtual void HandleEvents(sf::Event EventHandle) override;
		virtual void Draw(sf::RenderWindow* Window) override;

		void CollidedWith(Collision* Other, bool** IntersectData);

		void SetCamera(sf::View* Cam){ Camera = Cam; }

	private:
		AnimManager* AnimMgr;
		int Anim_Idle, Anim_Run, Anim_Jump, Anim_Fall;
		float Speed;
		float Grav;
		float Gravity;
		float MaxJump;
		bool bTouchingGround;

		sf::Time m_DeltaTime;
		sf::View* Camera;
		sf::FloatRect CameraBounds;

		bool m_ICollide;
		bool m_OnPlatform;

};

