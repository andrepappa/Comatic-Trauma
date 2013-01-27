#include "HeartBeatMonitor.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "WiimoteBindings.h"

HeartBeatMonitor::HeartBeatMonitor()
{
	/*std::vector<sf::IntRect*> Frames_Idle = AnimManager::GetSubRects(199, 328, 1, 8, 0, 0);*/
	std::vector<sf::IntRect*> Rects = AnimManager::GetSubRects(300, 195, 30, 6, 0,0);
	m_HeartBeatSpeed = 10;
	m_HBAnimManage = new AnimManager;
	m_HBIndex = m_HBAnimManage->AddAnim(Rects, m_HeartBeatSpeed);
	m_GOSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/HeartMonitor.png"));
	m_GOSprite->setPosition(10, 10);
	m_GOSprite->setTextureRect(*Rects[0]);
	StartPlaying = false;
	counterbaggascheize = 0;
	DoubleBeatClock.restart();
	DoubleBeatCheck = true;
	FlatlineCheck = false;
	bDead = false;
}


HeartBeatMonitor::~HeartBeatMonitor()
{
}

void HeartBeatMonitor::SetBeatSpeed(float HeartBeatSpeed)
{
	m_HeartBeatSpeed = HeartBeatSpeed;
	m_HBAnimManage->ChangeFrameTime(m_HBIndex, m_HeartBeatSpeed);
}


void HeartBeatMonitor::Update(sf::Time TimeDelta)
{
	//std::cout << "HeartBeat: " << m_HeartBeatSpeed << "\n";
	m_HBAnimManage->Update();
	if (DoubleBeatClock.getElapsedTime().asMilliseconds() > 150)
	{
		if (!DoubleBeatCheck)
		{
			if (m_HeartBeatSpeed<=40)
			{
				BeatInstance.BeatSound1.play();
			}
		}
		DoubleBeatCheck = true;
	}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	m_HeartBeatSpeed ++;
	//	m_HBAnimManage->ChangeFrameTime(m_HBIndex, m_HeartBeatSpeed);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	m_HeartBeatSpeed --;
	//	m_HBAnimManage->ChangeFrameTime(m_HBIndex, m_HeartBeatSpeed);
	//}
	//std::cout << m_HeartBeatSpeed << std::endl;
	if(m_HBAnimManage->NewFrame(m_HBIndex))
	{
		m_GOSprite->setTextureRect(*m_HBAnimManage->GetFrame(m_HBIndex));
		if (m_HBAnimManage->GetFrame(m_HBIndex)->top == 195 &&  m_HBAnimManage->GetFrame(m_HBIndex)->left == 1500 )
		{
			WiimoteBindings::setRumble(70);
			//BeatInstance.BeatSound2.play();
			if (m_HeartBeatSpeed>30 && m_HeartBeatSpeed<=40)
			{
				BeatInstance.BeatSound1.play();
				DoubleBeatClock.restart();
				DoubleBeatCheck = false;
			}
			if (m_HeartBeatSpeed>40)
			{
				if (!FlatlineCheck)
				{
					BeatInstance.BeatSound3.play();
					FlatlineCheck = true;
					bDead = true;
					m_GOSprite->setTexture(*ImageManager::RequestTexture("Assets\\GraphicalAssets\\heart monitor_dead01.png"));
				}
			}
		}
		if (m_HBAnimManage->GetFrame(m_HBIndex)->top == 195*2 &&  m_HBAnimManage->GetFrame(m_HBIndex)->left == 600 )
		{
			if (m_HeartBeatSpeed<50)
			{
				BeatInstance.BeatSound2.play();
			}
		}

		if (StartPlaying)
			BeatInstance.Update();

		if (counterbaggascheize == 4)
		{
			counterbaggascheize = 0;
			StartPlaying = false;
		}
	}
	
	

}

void HeartBeatMonitor::HandleEvents(sf::Event EventHandler)
{

}

void HeartBeatMonitor::Draw(sf::RenderWindow* Window)
{
	Window->draw(*m_GOSprite);

}