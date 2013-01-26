<<<<<<< HEAD
#pragma once
#include "phoenixengine\core\gamestate.h"

class Paralax :
	public GameState
{
public:
	~Paralax(void);

	void Init();

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

private:
	sf::Sprite* m_FarBg;
	sf::Sprite* m_MediumBg;
	sf::Sprite* m_Foreground;

	sf::View* LevelCamera;
//	sf::View* FarCamera;
//	sf::View* MidCamera;

	float m_Speed;
	float m_DirX;

};

=======
#pragma once
#include "phoenixengine\core\gamestate.h"
class Paralax :
	public GameState
{
public:
	~Paralax(void);

	void Init();

	virtual void Update(sf::Time DeltaTime) override;
	virtual void HandleEvents(sf::Event EventHandle) override;
	virtual void Draw(sf::RenderWindow* Window) override;

private:
	sf::Sprite* m_FarBg;
	sf::Sprite* m_MediumBg;
	sf::Sprite* m_Foreground;

	sf::View* LevelCamera;
	sf::View* FarCamera;
	sf::View* MidCamera;

	float m_Speed;
	float m_DirX;

};

>>>>>>> leupdate
