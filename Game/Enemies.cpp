#include "Enemies.h"


Enemies::Enemies()
{

	AnimMgr = new AnimManager();
	Anim_Idle, Anim_Run, Anim_Jump, Anim_Fall;
	std::vector<sf::IntRect*> Frames_Run = AnimManager::GetSubRects(199, 328, 8, 8, 0, 0);

	m_GOSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/player.png"));
	CollisionRef = m_GOSprite;
	m_GOSprite->setPosition(250.0f, 400.0f);
	Speed = 50;
}

void Enemies::HandleEvents(sf::Event EventHandle)
{

}

Enemies::~Enemies()
{
}

void Enemies::Update(sf::Time DeltaTime)
{
	if(m_GOSprite->getPosition().x >= target.x-10 && m_GOSprite->getPosition().x <= target.x+10)
	{
		target.x = m_GOSprite->getPosition().x + rand() % (200 - (-200)) + 1 + (-200);
	}
	else if (m_GOSprite->getPosition().x >= target.x)
	{
		m_GOSprite->move(-Speed*DeltaTime.asSeconds(),0.0f);
	}
	else
	{
		m_GOSprite->move(Speed*DeltaTime.asSeconds(),0.0f);
	}

	if(m_GOSprite->getPosition().y >= target.y-10 && m_GOSprite->getPosition().y <= target.y+10)
	{
		target.y = m_GOSprite->getPosition().y + rand() % (200 - (-200)) + 1 + (-200);
	}
	else if (m_GOSprite->getPosition().y >= target.y)
	{
		m_GOSprite->move(0,-Speed*DeltaTime.asSeconds());
	}
	else
	{
		m_GOSprite->move(0,Speed*DeltaTime.asSeconds());
	}
	std::cout << "Target: \nX: " << target.x << "\nY: " << target.y << std::endl;
	std::cout << Speed*DeltaTime.asSeconds() << std::endl;
}

void Enemies::Draw(sf::RenderWindow* window)
{
	window->draw(*m_GOSprite);
}