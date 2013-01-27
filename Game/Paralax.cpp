#include "Paralax.h"

#include "PhoenixEngine\Core\ImageManager.h"


Paralax::~Paralax()
{
	delete m_FarBg;
	delete m_MediumBg;
	delete m_Foreground;
	delete m_FarBg2;
	delete m_MediumBg2;
	delete m_Foreground2;
}


Paralax::Paralax()
{
	m_FarBg = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/background2.png"));
	m_FarBg2 = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/background2.png"));
	m_MediumBg = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/background2ochetthalvt.png"));
	m_MediumBg2 = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/background2ochetthalvt.png"));
	m_Foreground = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Paralax/level_prototype_cloud.png"));
	m_Foreground2 = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Paralax/level_prototype_cloud.png"));

	m_Foreground2->move(m_Foreground->getTextureRect().width, 0);
	m_MediumBg2->move(m_MediumBg->getTextureRect().width, 0);
	m_FarBg2->move(m_FarBg->getTextureRect().width, 0);
	m_Far_Scroll = sf::Vector2f(0.2f, 0.0f);
	m_Medium_Scroll = sf::Vector2f(0.5f, 0.2f);
	m_Fore_Scroll = sf::Vector2f(1, 1);
	CollisionRef = m_Foreground;
	LastCam = sf::Vector2f(0, 0);
	Camera = nullptr;
}

void Paralax::Update(sf::Time Deltatime) 
{
	if(Camera != nullptr)
	{
		sf::Vector2f CamPos( (Camera->getCenter().x-(Camera->getSize().x/2)), (Camera->getCenter().y-(Camera->getSize().y/2)) );
		if(LastCam != CamPos)
		{
			sf::Vector2f Diff(CamPos.x - LastCam.x, CamPos.y - LastCam.y);
			sf::Vector2f PixelsToMove_Far(Diff.x*(1-m_Far_Scroll.x), Diff.y*(1-m_Far_Scroll.y));
			sf::Vector2f PixelsToMove_Medium(Diff.x*(1-m_Medium_Scroll.x), Diff.y*(1-m_Medium_Scroll.y));
			sf::Vector2f PixelsToMove_Fore(Diff.x*(1-m_Fore_Scroll.x), Diff.y*(1-m_Fore_Scroll.y));

			m_FarBg->move(PixelsToMove_Far.x, PixelsToMove_Far.y);
			m_FarBg2->move(PixelsToMove_Far.x, PixelsToMove_Far.y);
			m_MediumBg->move(PixelsToMove_Medium.x, PixelsToMove_Medium.y);
			m_MediumBg2->move(PixelsToMove_Medium.x, PixelsToMove_Medium.y);
			m_Foreground->move(PixelsToMove_Fore.x, PixelsToMove_Fore.y);
			m_Foreground2->move(PixelsToMove_Fore.x, PixelsToMove_Fore.y);

			sf::Vector2f CamEnd(CamPos.x + Camera->getViewport().width, CamPos.y + Camera->getViewport().height);

			if(m_Foreground->getPosition().x + m_Foreground->getTextureRect().width < CamPos.x)
				m_Foreground->move(m_Foreground->getTextureRect().width*2, 0);
			if(m_Foreground2->getPosition().x + m_Foreground2->getTextureRect().width < CamPos.x)
				m_Foreground2->move(m_Foreground2->getTextureRect().width*2, 0);

			if(m_MediumBg->getPosition().x + m_MediumBg->getTextureRect().width < CamPos.x)
				m_MediumBg->move(m_MediumBg->getTextureRect().width*2, 0);
			if(m_MediumBg2->getPosition().x + m_MediumBg2->getTextureRect().width < CamPos.x)
				m_MediumBg2->move(m_MediumBg2->getTextureRect().width*2, 0);

			if(m_FarBg->getPosition().x + m_FarBg->getTextureRect().width < CamPos.x)
				m_FarBg->move(m_FarBg->getTextureRect().width*2, 0);
			if(m_FarBg2->getPosition().x + m_FarBg2->getTextureRect().width < CamPos.x)
				m_FarBg2->move(m_FarBg2->getTextureRect().width*2, 0);


			if(m_Foreground->getPosition().x > CamEnd.x + m_Foreground->getTextureRect().width)
				m_Foreground->move(-m_Foreground->getTextureRect().width*2, 0);
			if(m_Foreground2->getPosition().x > CamEnd.x + m_Foreground2->getTextureRect().width)
				m_Foreground2->move(-m_Foreground2->getTextureRect().width*2, 0);

			if(m_MediumBg->getPosition().x > CamEnd.x + m_MediumBg->getTextureRect().width)
				m_MediumBg->move(-m_MediumBg->getTextureRect().width*2, 0);
			if(m_MediumBg2->getPosition().x > CamEnd.x + m_MediumBg2->getTextureRect().width)
				m_MediumBg2->move(-m_MediumBg2->getTextureRect().width*2, 0);

			if(m_FarBg->getPosition().x > CamEnd.x + m_FarBg->getTextureRect().width)
				m_FarBg->move(-m_FarBg->getTextureRect().width*2, 0);
			if(m_FarBg2->getPosition().x > CamEnd.x + m_FarBg2->getTextureRect().width)
				m_FarBg2->move(-m_FarBg2->getTextureRect().width*2, 0);
		}

		LastCam = CamPos;
	}
}

bool Paralax::CheckCollision(Collision* Other, bool bNotify /* = true */)
{
	CollisionRef = m_Foreground;
	bool b1 = Collision::CheckCollision(Other, bNotify);
	CollisionRef = m_Foreground2;
	bool b2 = Collision::CheckCollision(Other, bNotify);

	return (b1 || b2);
}

void Paralax::HandleEvents(sf::Event HandleEvents)
{

}

void Paralax::Draw(sf::RenderWindow* Window) 
{
	Window->draw(*m_FarBg);
	Window->draw(*m_FarBg2);
	Window->draw(*m_MediumBg);
	Window->draw(*m_MediumBg2);
	Window->draw(*m_Foreground);
	Window->draw(*m_Foreground2);
}