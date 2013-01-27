#pragma once
#include "GameObject.h"
class Paralax :
	public GameObject
{
public:
	Paralax();
	~Paralax(void);

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;
	virtual bool CheckCollision(Collision* Other, bool bNotify = true) override;
	sf::View* Camera;

private:
	sf::Vector2f LastCam;
	sf::Sprite* m_FarBg, *m_FarBg2;
	sf::Sprite* m_MediumBg, *m_MediumBg2;
	sf::Sprite* m_Foreground, *m_Foreground2;
	sf::Vector2f m_Far_Scroll, m_Medium_Scroll, m_Fore_Scroll;
};