#include <SFML/Graphics.hpp>
#include "LevelOne.h"
#include "StateMenu.h"
#include "Background.h"
#include "PhoenixEngine\Core\PhoenixEngine.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "Obstacle.h"
#include "Paralax.h"
#include "Player.h"
#include "Enemies.h"

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

	Camera = new sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
	ParallaxBg->Camera = Camera;
	Background* BG = new Background;
	BG->SetCamera(Camera);
	ThePlayer = new Player;
	ThePlayer->SetCamera(Camera);
	m_LOObjects.push_back(ParallaxBg);
	m_LOObjects.push_back(ThePlayer);

	std::vector<sf::Vector2f> FP;

	FP.push_back(sf::Vector2f(1116, 300));
	FP.push_back(sf::Vector2f(1760, 600));
	FP.push_back(sf::Vector2f(2245, 535));
	FP.push_back(sf::Vector2f(2967, 558));
	FP.push_back(sf::Vector2f(3991, 210));
	FP.push_back(sf::Vector2f(3792, -230));
	FP.push_back(sf::Vector2f(5466, 83));
	FP.push_back(sf::Vector2f(7712, 440));
	FP.push_back(sf::Vector2f(8552, -230));
	FP.push_back(sf::Vector2f(9297, 500));
	FP.push_back(sf::Vector2f(10449, -230));
	FP.push_back(sf::Vector2f(11873, 86));
	FP.push_back(sf::Vector2f(6082, 467));
	FP.push_back(sf::Vector2f(7651, -150));
	FP.push_back(sf::Vector2f(10480, 359));

	//Fragments 0 < X < 12000
	//Fragments 0 < Y < 720

	for(unsigned int i = 0; i < FP.size(); i++)
	{
		Fragment* Frag = new Fragment();
		Frag->setPosition(FP[i].x, FP[i].y);
		m_LOObjects.push_back(Frag);
	}

	for(unsigned int i = 0; i < 5; i++)
	{
		Enemies* Enemy = new Enemies();
		Enemy->setPosition(sf::Vector2f(rand()%12000, rand()&720));
		Enemy->setPlayer(ThePlayer);
		m_LOObjects.push_back(Enemy);
	}

	HealthTimerInterval = sf::milliseconds(200);
	HealthTimer.restart();
	bGameOver = false;


	HitSoundBuffer.loadFromFile("Hit.ogg");
	HitSound.setBuffer(HitSoundBuffer);
	FragmentSoundBuffer.loadFromFile("Fragment.ogg");
	FragmentSound.setBuffer(FragmentSoundBuffer);

	LastEnemyHitTime = sf::Time();
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
		ThePlayer->bDead = true;
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
					FragmentSound.play();
					delete Frag;
					m_LOObjects.erase(m_LOObjects.begin() + j);
					//Fragment* F = new Fragment();
					//F->setPosition(ThePlayer->getPos().x + 500, ThePlayer->getPos().y - 200);
					//m_LOObjects.push_back(F);
					Heartmon->SetBeatSpeed(5.0f);
					ThePlayer->PowerChange(Heartmon->GetBeatSpeed());
				}
				else
				{
					Enemies* Enemy = dynamic_cast<Enemies*>(m_LOObjects[j]);
					if(P != NULL && Enemy != NULL)
					{
						if(EnemyHitProtection.getElapsedTime() - LastEnemyHitTime >= sf::seconds(1))
						{
							HitSound.play();
							Heartmon->SetBeatSpeed(Heartmon->GetBeatSpeed()+5.0f);
							ThePlayer->PowerChange(Heartmon->GetBeatSpeed());

							LastEnemyHitTime = EnemyHitProtection.getElapsedTime();
						}
					}
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

