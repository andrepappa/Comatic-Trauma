#pragma once
#include "gameobject.h"
#include "AnimManager.h"
#include "Beat.h"

class HeartBeatMonitor :
	public GameObject
{
public:
	HeartBeatMonitor();
	~HeartBeatMonitor();

	virtual void Update(sf::Time DeltaTime);
	virtual void HandleEvents(sf::Event EventHandle);
	virtual void Draw(sf::RenderWindow* Window);

	void SetBeatSpeed(float HeartBeatSpeed);

private:
	Beat BeatInstance;
	float m_HeartBeatSpeed;
	sf::Clock DoubleBeatClock;
	bool DoubleBeatCheck;
	AnimManager* m_HBAnimManage;
//	sf::Sprite* m_HBSprite;
	int m_HBIndex;
	bool StartPlaying;
	int counterbaggascheize;
};

