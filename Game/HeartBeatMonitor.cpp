#include "HeartBeatMonitor.h"
#include "PhoenixEngine\Core\ImageManager.h"
#include "WiimoteBindings.h"

HeartBeatMonitor::HeartBeatMonitor()
{
	/*std::vector<sf::IntRect*> Frames_Idle = AnimManager::GetSubRects(199, 328, 1, 8, 0, 0);*/
	std::vector<sf::IntRect*> Rects = AnimManager::GetSubRects(300, 195, 30, 6, 0,0);
	m_HeartBeatSpeed = 10;//31.915f;
	m_HBAnimManage = new AnimManager;
	m_HBIndex = m_HBAnimManage->AddAnim(Rects, m_HeartBeatSpeed);
	m_GOSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/HeartMonitor.png"));
	m_GOSprite->setPosition(10, 10);
	m_GOSprite->setTextureRect(*Rects[0]);
	StartPlaying = false;
	counterbaggascheize = 0;
	DoubleBeatClock.restart();
	DoubleBeatCheck = false;
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
			BeatInstance.BeatSound1.play();
		}
		DoubleBeatCheck = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_HeartBeatSpeed ++;
		m_HBAnimManage->ChangeFrameTime(m_HBIndex, m_HeartBeatSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_HeartBeatSpeed --;
		m_HBAnimManage->ChangeFrameTime(m_HBIndex, m_HeartBeatSpeed);
	}
	//std::cout << m_HeartBeatSpeed << std::endl;
	if(m_HBAnimManage->NewFrame(m_HBIndex))
	{
		m_GOSprite->setTextureRect(*m_HBAnimManage->GetFrame(m_HBIndex));
		if (m_HBAnimManage->GetFrame(m_HBIndex)->top == 195 &&  m_HBAnimManage->GetFrame(m_HBIndex)->left == 1500 )
		{
			WiimoteBindings::setRumble(70);
			BeatInstance.BeatSound1.play();
			DoubleBeatClock.restart();
			DoubleBeatCheck = false;
			//StartPlaying = true;
//			m_HBAnimManage->ChangeFrameTime(m_HBIndex, 34);

			counterbaggascheize++;
		}
//		std::cout << "\nDebug: "  << m_HBAnimManage->GetFrame(m_HBIndex)->top << "\t:" << m_HBAnimManage->GetFrame(m_HBIndex)->left << std::endl;

//		if (m_HBAnimManage->GetFrame(m_HBIndex)->top == 195*4 &&  m_HBAnimManage->GetFrame(m_HBIndex)->left == 1500)
//		{
//			StartPlaying = false;
////			m_HBAnimManage->ChangeFrameTime(m_HBIndex, 31);
//		}

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