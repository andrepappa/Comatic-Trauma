#include "Player.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\Utility.h"

#include "Background.h"

Player::Player()
{
	CameraBounds = sf::FloatRect(240, 150, 400, 420);
	Camera = nullptr;
	m_GOSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/ship.png"));
	CollisionRef = m_GOSprite;
	Speed = 500.0f;
	m_GOSprite->setPosition(250.0f, 400.0f);
	PosX = 0.0f;
	PosY = 0.0f;
	DirectionX = 0.0f;
	DirectionY = 0.0f;
	JumpDefault = 1400.0f;
	JumpSpeed = 1400.0f;
	JumpReduce = 55.0f;
	Jumping = false;
	Falling = false;
}


Player::~Player()
{
	delete m_GOSprite;
}

void Player::CollidedWith(Collision* Other)
{
	Background* BG = dynamic_cast<Background*>(Other);

	if(BG != NULL)
	{
		Util::msgNote("Collided With World!");
	}
}

void Player::Draw(sf::RenderWindow* window)
{
	sf::RectangleShape Rect(sf::Vector2f(CameraBounds.width, CameraBounds.height));
	Rect.setPosition(CameraBounds.left, CameraBounds.top);
	Rect.setFillColor(sf::Color(0, 255, 0));
	
	window->setView(window->getDefaultView());
	window->draw(Rect);
	window->setView(*Camera);
	window->draw(*m_GOSprite);
}

void Player::HandleEvents(sf::Event EventHandle) 
{
	
}

void Player::Update(sf::Time DeltaTime) 
{
	DirectionX = 0.0f;
	DirectionY = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space ))
	{
		DirectionY = -1.0f;

		Jumping = true;

	}
	else
	{
		if (!Falling && !(JumpSpeed <= 500))
		{
			Falling = true;
			JumpSpeed = 500;
		}
	}


	if (Jumping)
	{
		DirectionY = -1.0f;
		JumpSpeed -= JumpReduce;
	}
	else
	{
		DirectionY = 0.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{

		DirectionX = -1.0f;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		DirectionX = 1.0f;
	}
	
	PosY = JumpSpeed * DirectionY * PhoenixEngine::DeltaTime.asSeconds();
	PosX = Speed * DirectionX * PhoenixEngine::DeltaTime.asSeconds();
	m_GOSprite->move(PosX, PosY);
	//Camera->move(PosX, PosY);
	if (m_GOSprite->getPosition().y > 500)
	{
		Jumping = false;
		JumpSpeed = JumpDefault;
		Falling = false;
		m_GOSprite->setPosition(m_GOSprite->getPosition().x,500.0f);
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
