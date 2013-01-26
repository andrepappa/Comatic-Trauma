#include <SFML/Graphics.hpp>
#include "LevelOne.h"
#include "StateTest.h"
#include "Background.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "Obstacle.h"

LevelOne::~LevelOne() 
{
	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		delete m_LOObjects[i];
	}
	delete Camera;
}


void LevelOne::Init()
{
	Camera = new sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
	Background* BG = new Background;
	BG->SetCamera(Camera);
	Player* PL = new Player;
	PL->SetCamera(Camera);
	m_LOObjects.push_back(BG);

	Obstacle* BoxCollTest = new Obstacle();
	sf::Sprite* CrashTestDummy = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/ornate_small1.png"));
	BoxCollTest->setSprite(CrashTestDummy);
	BoxCollTest->CollisionRef = CrashTestDummy;
	CrashTestDummy->setPosition(400.0f, 400.0f);
	m_LOObjects.push_back(BoxCollTest);
	m_LOObjects.push_back(PL);

	Obstacle* BoxCollTest2 = new Obstacle();
	sf::Sprite* CrashDummy2 = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/ornate_small1.png"));
	BoxCollTest2->setSprite(CrashDummy2);
	BoxCollTest2->CollisionRef = CrashDummy2;
	CrashDummy2->setPosition(900.0f, 500.0f);
	m_LOObjects.push_back(BoxCollTest2);

}

void LevelOne::Update(sf::Time DeltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		Camera->move(15, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		Camera->move(-15, 0);
	// movment update 
	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		m_LOObjects[i]->Update(DeltaTime);
	}
	for (unsigned int i = 0; i < m_LOObjects.size()-1; i++)
	{
		for (unsigned int j = (i+1); j < m_LOObjects.size(); j++)
		{
			if (m_LOObjects[i]->CheckCollision(m_LOObjects[j]))
			{
				std::cout << "We are colliding" << std::endl;
				

			}
			
		}
	}

}

void LevelOne::HandleEvents(sf::Event EventHandle)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		PhoenixEngine::GetInstance()->QueueState(new StateTest);
		std::cout << "In Level1"; // jumping jacks
		
	}
	
	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		m_LOObjects[i]->HandleEvents(EventHandle);
	}


}

void LevelOne::Draw(sf::RenderWindow* Window)
{
	Window->setView(*Camera);

	for (unsigned int i = 0; i < m_LOObjects.size(); i++)
	{
		m_LOObjects[i]->Draw(Window);
	}
	Window->setView(Window->getDefaultView());

}
