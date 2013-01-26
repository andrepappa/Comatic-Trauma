#include "Paralax.h"

#include "PhoenixEngine\Core\ImageManager.h"


Paralax::~Paralax()
{
}


void Paralax::Init()
{
	m_FarBg = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Paralax/plaxbgproto.png"));
	m_MediumBg = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Paralax/plaxmid.png"));
	m_Foreground = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Paralax/level_prototype_cloud.png"));

	LevelCamera = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	MidCamera = new sf::View(sf::FloatRect(0,0,1280,720));
	FarCamera = new sf::View(sf::FloatRect(0,0,1280,720));

	m_Speed = 50.0f;
	m_DirX = 0.0f;
}

void Paralax::Update(sf::Time Deltatime) 
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Camera->move(1.0f, 0.0f);
		m_DirX = 1.0f;

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Camera->move(-1.0f, 0.0f);
		m_DirX = -1.0f;
	}

	LevelCamera->move(m_Speed * m_DirX * Deltatime.asSeconds(), 0.0f);
	m_FarBg->move(m_Speed * 0.3f * m_DirX * Deltatime.asSeconds(), 0.0f);
	m_MediumBg->move(m_Speed * 0.6f * m_DirX * Deltatime.asSeconds(), 0.0f);
}

void Paralax::HandleEvents(sf::Event HandleEvents)
{

}

void Paralax::Draw(sf::RenderWindow* Window) 
{
//	Window->setView(*FarCamera);
//	Window->setView(*MidCamera);
	Window->setView(*LevelCamera);
	Window->draw(*m_FarBg);
	Window->draw(*m_MediumBg);
	Window->draw(*m_Foreground);
}