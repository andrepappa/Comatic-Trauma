#include "Background.h"
#include "PhoenixEngine\Core\ImageManager.h"


Background::Background()
{
	Camera = nullptr;
	ParallaxImage* PI = new ParallaxImage();
	PI->Sprites[0] = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/level_jump_prototype.png"));
	PI->Sprites[1] = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/level_jump_prototype.png"));
	PI->Sprites[1]->setPosition(1280.0f, 0.0f);
	CollisionRef = PI->Sprites[0];
	m_Backgrounds.push_back(PI);
}


Background::~Background()
{
	for(unsigned int i = 0; i < m_Backgrounds.size(); i++)
	{
		delete m_Backgrounds[i]->Sprites[0];
		delete m_Backgrounds[i]->Sprites[1];
		delete m_Backgrounds[i];
	}
	m_Backgrounds.clear();
}


void Background::Update(sf::Time DeltaTime)
{

}

void Background::HandleEvents(sf::Event EventHandle)
{

}

void Background::Draw(sf::RenderWindow* Window)
{
	for (unsigned int i = 0; i < m_Backgrounds.size(); i++)
	{
		Window->draw(*m_Backgrounds[i]->Sprites[0]);
		Window->draw(*m_Backgrounds[i]->Sprites[1]);
	}
}