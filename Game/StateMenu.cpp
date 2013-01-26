#include "StateMenu.h"

#include "PhoenixEngine/Core/ImageManager.h"
void StateMenu::Init()
{
	Anims = new AnimManager;
	std::vector<sf::IntRect*> Rects = Anims->GetSubRects(1280, 720, 60, 8, 0, 0);
	//BgAnimIndex = Anims->AddAnim(Rects, 66);
	//BgAnim = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Menu/BackgroundAnim.png", true));
	//BgAnim->setPosition(0, 0);
	//StaticOverlay = new sf::Sprite(*ImageManager::RequestTexture("Assets/GraphicalAssets/Menu/Text.png"));
	//StaticOverlay->setPosition(0,0);
}

StateMenu::~StateMenu()
{
}

void StateMenu::Update(sf::Time DeltaTime)
{
	//Anims->Update();
	//if(Anims->NewFrame(BgAnimIndex))
	//	BgAnim->setTextureRect(*Anims->GetFrame(BgAnimIndex));
}

void StateMenu::HandleEvents(sf::Event EventHandle)
{
}

void StateMenu::Draw(sf::RenderWindow* Window)
{
	//Window->draw(*BgAnim);
	//Window->draw(*StaticOverlay);
}