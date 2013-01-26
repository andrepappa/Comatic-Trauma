#include <SFML/Graphics.hpp>
#include "LevelOne.h"
#include "StateTest.h"
#include "Background.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\ImageManager.h"

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
	m_LOObjects.push_back(PL);
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
			m_LOObjects[i]->CheckCollision(m_LOObjects[j]);
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
