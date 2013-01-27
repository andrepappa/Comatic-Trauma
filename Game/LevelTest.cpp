#include <SFML/Graphics.hpp>
#include "LevelTest.h"
#include "StateTest.h"
#include "Background.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "Obstacle.h"

LevelTest::~LevelTest() 
{
	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		delete m_LOObjects[i];
	}
	delete Camera;
}


void LevelTest::Init()
{
	Camera = new sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));

	Enemies* Enemy = new Enemies();
	sf::Sprite* EnemySprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/ship.png"));
	//Enemy->setSprite(EnemySprite);
	Enemy->CollisionRef = EnemySprite;
	EnemySprite->setPosition(500.0f, 500.0f);
	m_LOObjects.push_back(Enemy);
	std::cout << "EnemyPos: \nX: " << EnemySprite->getPosition().x << "\nY: " << EnemySprite->getPosition().y << std::endl;
}

void LevelTest::Update(sf::Time DeltaTime)
{
	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		m_LOObjects[i]->Update(DeltaTime);
	}
}

void LevelTest::HandleEvents(sf::Event EventHandle)
{
	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		m_LOObjects[i]->HandleEvents(EventHandle);
	}
}

void LevelTest::Draw(sf::RenderWindow* Window)
{
	Window->setView(*Camera);

	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		m_LOObjects[i]->Draw(Window);
	}
	Window->setView(Window->getDefaultView());

}
