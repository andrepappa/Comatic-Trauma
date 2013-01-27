#include "Enemies.h"


Enemies::Enemies()
{

	AnimMgr = new AnimManager();
	std::vector<sf::IntRect*> Rects = AnimManager::GetSubRects(118, 210, 7, 4, 0, 0);
	EnemyAnim = AnimMgr->AddAnim(Rects, 32);
	m_GOSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/wwraith test.png"));
	CollisionRef = m_GOSprite;
	m_GOSprite->setPosition(0, 0);
	sf::Color c = m_GOSprite->getColor();
	c.a = 150;
	m_GOSprite->setColor(c);
	Speed = 700;
	target.x = m_GOSprite->getPosition().x + 100;
	bLastDirWasLeft = false;
	ReTargetDelay = sf::seconds(2.0f);
}

void Enemies::HandleEvents(sf::Event EventHandle)
{

}

Enemies::~Enemies()
{
}

void Enemies::Update(sf::Time DeltaTime)
{
	AnimMgr->Update();
	if(AnimMgr->NewFrame(EnemyAnim))
		m_GOSprite->setTextureRect(*AnimMgr->GetFrame(EnemyAnim));

	if(ReTargetTimer.getElapsedTime() > ReTargetDelay)
	{
		ReTargetTimer.restart();
		target.x = PlayerTarget->getPos().x + ( (rand()%600) - 100 );
		target.y = PlayerTarget->getPos().y + ( (rand()%400) - 200 );
	}

	if (m_GOSprite->getPosition().x >= target.x)
	{
		if(m_GOSprite->getPosition().x < target.x - 50 || m_GOSprite->getPosition().x > target.x + 50)
		{
			m_GOSprite->setTexture(*ImageManager::RequestTexture("Assets/GraphicalAssets/wwraith test.png"));
			m_GOSprite->move(-Speed*DeltaTime.asSeconds(),0.0f);
		}
	}
	else
	{
		if(m_GOSprite->getPosition().x < target.x - 50 || m_GOSprite->getPosition().x > target.x + 50)
		{
			m_GOSprite->setTexture(*ImageManager::RequestTexture("Assets/GraphicalAssets/wwraith testr.png"));
			m_GOSprite->move(Speed*DeltaTime.asSeconds(),0.0f);
		}
	}
	
	if (m_GOSprite->getPosition().y >= target.y)
	{
		if(m_GOSprite->getPosition().y < target.y - 50 || m_GOSprite->getPosition().y > target.y + 50)
			m_GOSprite->move(0,-Speed*DeltaTime.asSeconds());
	}
	else
	{
		if(m_GOSprite->getPosition().y < target.y - 50 || m_GOSprite->getPosition().y > target.y + 50)
			m_GOSprite->move(0,Speed*DeltaTime.asSeconds());
	}
	//std::cout << "Target: \nX: " << target.x << "\nY: " << target.y << std::endl;
	//std::cout << Speed*DeltaTime.asSeconds() << std::endl;
}

void Enemies::Draw(sf::RenderWindow* window)
{
	window->draw(*m_GOSprite);
}