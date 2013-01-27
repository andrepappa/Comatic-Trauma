#include <SFML/Graphics.hpp>
#include "LevelOne.h"
#include "StateMenu.h"
#include "Background.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "Obstacle.h"
#include "Paralax.h"
#include <algorithm>

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


	//RanFrag = new Fragment();
	//sf::Sprite* FragmntCrashRef = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Fragments/Fragments0001.png"));
	//RanFrag->CollisionRef = FragmntCrashRef;

	//RanFrag->setPosition(500.0f, 200.0f);

	HealthTimerInterval = sf::milliseconds(200);
	HealthTimer.restart();
}

void LevelOne::Update(sf::Time DeltaTime)
{
	if(HealthTimer.getElapsedTime() > HealthTimerInterval)
	{
		HealthTimer.restart();
		Heartmon->SetBeatSpeed(Heartmon->GetBeatSpeed()+0.25f);
		ThePlayer->PowerChange(Heartmon->GetBeatSpeed());
	}

	Heartmon->Update(DeltaTime);
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
				
				 
			}
			
		}
	}
	Anims->Update();
	if(Anims->NewFrame(BgAnimIndex))
		m_SmokeSprite->setTexture(*m_SmokeBorder[Anims->CurFrame(BgAnimIndex)]);

}

void LevelOne::HandleEvents(sf::Event EventHandle)
{
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

