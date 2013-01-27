#include <SFML/Graphics.hpp>
#include "LevelOne.h"
#include "StateMenu.h"
#include "Background.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "Obstacle.h"
#include "Paralax.h"
#include <algorithm>
#include "Player.h"

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
	Paralax* ParallaxBg = new Paralax;
	Heartmon = new HeartBeatMonitor;
	Anims = new AnimManager;
	std::vector<sf::IntRect*> Rects;
	for(int i = 0; i < 40; i+=4)
		Rects.push_back(nullptr);
	
	BgAnimIndex = Anims->AddAnim(Rects, 48);

	for (int i = 0; i < 40; i+=4)
	{
		std::string path;
		path = Util::BuildString("Assets/GraphicalAssets/Smoke/Comp 2_00%03d.png", i);
		m_SmokeBorder.push_back(ImageManager::RequestTexture(path));
	}

	m_SmokeSprite = new sf::Sprite(*m_SmokeBorder[0]);


	m_SmokeSprite->setPosition(0, 0);
//	StaticOverlay = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Menu/Text.png"));
//	StaticOverlay->setPosition(0,0);

	Camera = new sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
	ParallaxBg->Camera = Camera;
	Background* BG = new Background;
	BG->SetCamera(Camera);
	ThePlayer = new Player;
	ThePlayer->SetCamera(Camera);
	m_LOObjects.push_back(ParallaxBg);
	m_LOObjects.push_back(ThePlayer);
	//m_LOObjects.push_back(BG);


	for(int i = 0; i < 50; i++)
	{
		Fragment* Frag = new Fragment();
		Frag->setPosition((rand()%4000)-2000, (rand()%1000)-500);
		m_LOObjects.push_back(Frag);
	}

	HealthTimerInterval = sf::milliseconds(200);
	HealthTimer.restart();
	bGameOver = false;
}

void LevelOne::Update(sf::Time DeltaTime)
{
	Heartmon->Update(DeltaTime);
	if(DeadRestartTimer.getElapsedTime().asSeconds() > 3.0f && bGameOver)
	{
		PhoenixEngine::QueueState(new LevelOne);
	}
	if(!bGameOver && (Heartmon->bDead || ThePlayer->getPos().y >= 750))
	{
		DeadRestartTimer.restart();
		Heartmon->SetBeatSpeed(40.f);
		bGameOver = true;
	}

	if(HealthTimer.getElapsedTime() > HealthTimerInterval)
	{
		HealthTimer.restart();
		Heartmon->SetBeatSpeed(Heartmon->GetBeatSpeed()+0.25f);
		ThePlayer->PowerChange(Heartmon->GetBeatSpeed());
	}

	//RanFrag->Update(DeltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		Camera->move(15, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		Camera->move(-15, 0);

	// movement update 
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
				//std::cout << "We are colliding" << std::endl;

				Player* P = dynamic_cast<Player*>(m_LOObjects[i]);
				Fragment* Frag = dynamic_cast<Fragment*>(m_LOObjects[j]);

				if (P != NULL && Frag != NULL)
				{
					delete Frag;
					m_LOObjects.erase(m_LOObjects.begin() + j);
					Heartmon->SetBeatSpeed(5.0f);
					ThePlayer->PowerChange(Heartmon->GetBeatSpeed());
				}
			}
			
		}
	}
	Anims->Update();
	if(Anims->NewFrame(BgAnimIndex))
		m_SmokeSprite->setTexture(*m_SmokeBorder[Anims->CurFrame(BgAnimIndex)]);

}

void LevelOne::HandleEvents(sf::Event EventHandle)
{
	if(bGameOver)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		PhoenixEngine::GetInstance()->QueueState(new StateMenu);
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
	Heartmon->Draw(Window);
	Window->draw(*m_SmokeSprite);
	//RanFrag->Draw(Window);
}

