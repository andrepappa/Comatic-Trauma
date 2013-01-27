#include "Player.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\Utility.h"
#include <iostream>
#include "Background.h"
#include "Paralax.h"
#include "Fragment.h"

#include "WiimoteBindings.h"

#include <vector>
Player::Player()
{
	GOType = PLAYER;
	CameraBounds = sf::FloatRect(240, 150, 400, 420);
	Camera = nullptr;
	AnimMgr = new AnimManager();

	std::vector<sf::IntRect*> Frames_Idle = AnimManager::GetSubRects(75, 120, 5, 9, 0, 2);
	std::vector<sf::IntRect*> Frames_Run = AnimManager::GetSubRects(75, 120, 18, 9, 0, 0);
	std::vector<sf::IntRect*> Frames_Jump = AnimManager::GetSubRects(75, 120, 1, 9, 5, 2);
	std::vector<sf::IntRect*> Frames_Fall = AnimManager::GetSubRects(75, 120, 1, 9, 6, 2);
	Anim_Idle = AnimMgr->AddAnim(Frames_Idle, 32);
	Anim_Run = AnimMgr->AddAnim(Frames_Run, 32);
	Anim_Jump = AnimMgr->AddAnim(Frames_Jump, 32);
	Anim_Fall = AnimMgr->AddAnim(Frames_Fall, 32);

	CurrentAnim = IDLE;
	m_GOSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/character02.png"));
	ImageManager::RequestTexture("Assets/GraphicalAssets/character02_2.png");
	m_GOSprite->setTextureRect(*Frames_Idle[0]);
	CollisionRef = m_GOSprite;
	m_GOSprite->setPosition(300.0f, 100.0f);

	Speed = 400;
	Grav = 0;
	Gravity = 30;
	MaxJump = -1350;
	bTouchingGround = false;
	bDead = false;
}


Player::~Player()
{
	delete m_GOSprite;
}

void Player::PowerChange(int HeartBeatSpeed)
{
	Speed = Util::Max(3000/HeartBeatSpeed, 10);
	AnimMgr->ChangeFrameTime(Anim_Idle, 6.4f*HeartBeatSpeed);
	AnimMgr->ChangeFrameTime(Anim_Run, 6.4f*HeartBeatSpeed);
	AnimMgr->ChangeFrameTime(Anim_Jump, 6.4f*HeartBeatSpeed);
	AnimMgr->ChangeFrameTime(Anim_Fall, 6.4f*HeartBeatSpeed);
}

sf::IntRect INTRECT, INTRECT2;
void Player::CollidedWith(Collision* Other, bool** IntersectData)
{
	if(bDead)
		return;
	Paralax* BG = dynamic_cast<Paralax*>(Other);
	if(BG != NULL)
	{
		sf::Rect<int> IntersectingRect;
		sf::IntRect SpriteRect(0,0,0,0), SpriteRectOther(0,0,0,0);
		SpriteRect.left = CollisionRef->getPosition().x;
		SpriteRect.top = CollisionRef->getPosition().y;
		SpriteRect.width = CollisionRef->getTextureRect().width;
		SpriteRect.height = CollisionRef->getTextureRect().height;
		SpriteRectOther.left = Other->CollisionRef->getPosition().x;
		SpriteRectOther.top = Other->CollisionRef->getPosition().y;
		SpriteRectOther.width = Other->CollisionRef->getTextureRect().width;
		SpriteRectOther.height = Other->CollisionRef->getTextureRect().height;

		SpriteRect.intersects(SpriteRectOther, IntersectingRect);

		int FirstX = -1, FirstY = -1;
		int LastX = -1, LastY = -1;

		for(int x = 0; x < IntersectingRect.width; x++)
		{
			for(int y = 0; y < IntersectingRect.height; y++)
			{
				if(IntersectData[x][y])
				{
					if(FirstX == -1 || FirstX > x)
						FirstX = x;
					if(FirstY == -1 || FirstY > y)
						FirstY = y;

					if(LastX == -1 || LastX < x)
						LastX = x;
					if(LastY == -1 || LastY < y)
						LastY = y;
				}
			}
		}

		sf::IntRect NewIntersectRect(IntersectingRect.left + FirstX, IntersectingRect.top + FirstY, LastX - FirstX, LastY - FirstY);

		bool bLeft = false, bRight = false, bCeiling = false, bFloor = false;

		//Floor
		if(NewIntersectRect.top > IntersectingRect.top + IntersectingRect.height/2)
			bFloor = true;

		//Ceiling
		if(NewIntersectRect.top < IntersectingRect.top + IntersectingRect.height/2)
			bCeiling = true;

		//Left
		if(NewIntersectRect.left > IntersectingRect.left + IntersectingRect.width/2)
			bLeft = true;

		//Right
		if(NewIntersectRect.left < IntersectingRect.left + IntersectingRect.width/2)
			bLeft = true;

		if(bFloor)
			bTouchingGround = true;
		else
			bTouchingGround = false;

		while(CheckCollision(Other, false))
		{
			if(bFloor || bCeiling)
			{
				if(bFloor)
					m_GOSprite->move(0, -Gravity*PhoenixEngine::DeltaTime.asSeconds());
				if(bCeiling)
					m_GOSprite->move(0, Gravity*PhoenixEngine::DeltaTime.asSeconds());
			}
			else
			{
				if(bLeft)
					m_GOSprite->move(-Speed*PhoenixEngine::DeltaTime.asSeconds(), 0);
				if(bRight)
					m_GOSprite->move(Speed*PhoenixEngine::DeltaTime.asSeconds(), 0);
			}
			Grav = 0;
		}

		INTRECT = IntersectingRect;
		INTRECT2 = NewIntersectRect;
	}
}

void Player::Draw(sf::RenderWindow* window)
{
	//sf::RectangleShape Rect1(sf::Vector2f(INTRECT.width, INTRECT.height));
	//Rect1.setPosition(INTRECT.left, INTRECT.top);
	//Rect1.setFillColor(sf::Color::Transparent);
	//Rect1.setOutlineColor(sf::Color::Red);
	//Rect1.setOutlineThickness(1);
	//sf::RectangleShape Rect2(sf::Vector2f(INTRECT2.width, INTRECT2.height));
	//Rect2.setPosition(INTRECT2.left, INTRECT2.top);
	//Rect2.setFillColor(sf::Color::Transparent);
	//Rect2.setOutlineColor(sf::Color::Green);
	//Rect2.setOutlineThickness(1);

	//sf::RectangleShape P(sf::Vector2f(m_GOSprite->getTextureRect().width, m_GOSprite->getTextureRect().height));
	//P.setPosition(m_GOSprite->getPosition());
	//P.setFillColor(sf::Color::Transparent);
	//P.setOutlineColor(sf::Color::Blue);
	//P.setOutlineThickness(1);
	window->draw(*m_GOSprite);
	//window->draw(P);
	//window->draw(Rect1);
	//window->draw(Rect2);
}

void Player::HandleEvents(sf::Event EventHandle) 
{
	
}

void Player::Update(sf::Time DeltaTime) 
{
	switch(CurrentAnim)
	{
		case IDLE:
			m_GOSprite->setTextureRect(*AnimMgr->GetFrame(Anim_Idle));
			break;
		case RUN:
			m_GOSprite->setTextureRect(*AnimMgr->GetFrame(Anim_Run));
			break;
		case JUMP:
			m_GOSprite->setTextureRect(*AnimMgr->GetFrame(Anim_Jump));
			break;
		case FALL:
			m_GOSprite->setTextureRect(*AnimMgr->GetFrame(Anim_Fall));
			break;
	}

	AnimMgr->Update();

	m_GOSprite->move(0, Grav*DeltaTime.asSeconds());
	Grav += Gravity;

	//if(m_GOSprite->getPosition().y > 1750)
	//{
	//	Grav = 0;
	//	bTouchingGround = true;
	//}

	if(Grav > 0 && !bTouchingGround)
		CurrentAnim = FALL;

	if(bTouchingGround && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || WiimoteBindings::isDown(UP)))
		CurrentAnim = RUN;
	else if(bTouchingGround && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || WiimoteBindings::isDown(DOWN)))
		CurrentAnim = RUN;
	else if(bTouchingGround)
		CurrentAnim = IDLE;
	//if(bTouchingGround && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	//	CurrentAnim = IDLE;
	//else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && bTouchingGround)
	//	CurrentAnim = RUN;


	if(!bDead)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || WiimoteBindings::isDown(UP))
		{
			m_GOSprite->move(-Speed*DeltaTime.asSeconds(), 0);
			m_GOSprite->setTexture(*ImageManager::RequestTexture("Assets/GraphicalAssets/character02_2.png"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || WiimoteBindings::isDown(DOWN))
		{
			m_GOSprite->move(Speed*DeltaTime.asSeconds(), 0);
			m_GOSprite->setTexture(*ImageManager::RequestTexture("Assets/GraphicalAssets/character02.png"));
		}

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || WiimoteBindings::isDown(ONE)) && bTouchingGround)
		{
			Grav = MaxJump;
			bTouchingGround = false;
			CurrentAnim = JUMP;
		}
	}else
	{
		CurrentAnim = FALL;
	}

	/* Convert CameraBounds to global coords */
	sf::Vector2f CameraBoundsGlobalCoords = PhoenixEngine::GetWindow()->convertCoords(sf::Vector2i(CameraBounds.left, CameraBounds.top), *Camera);

	/* Do checks if Player is outside of CameraBounds(global) */
	if(m_GOSprite->getPosition().x < CameraBoundsGlobalCoords.x)
		Camera->move(-Speed * DeltaTime.asSeconds(), 0.0f);
	if(m_GOSprite->getPosition().x + m_GOSprite->getTextureRect().width > CameraBoundsGlobalCoords.x + CameraBounds.width)
		Camera->move(Speed * DeltaTime.asSeconds(), 0.0f);

	if(m_GOSprite->getPosition().y < CameraBoundsGlobalCoords.y)
		Camera->move(0.0f, m_GOSprite->getPosition().y - CameraBoundsGlobalCoords.y);
	if(m_GOSprite->getPosition().y + m_GOSprite->getTextureRect().height > CameraBoundsGlobalCoords.y + CameraBounds.height)
		Camera->move(0.0f, (m_GOSprite->getPosition().y + m_GOSprite->getTextureRect().height) - (CameraBoundsGlobalCoords.y + CameraBounds.height));
}