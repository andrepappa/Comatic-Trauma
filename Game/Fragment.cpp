#include "Fragment.h"
#include "PhoenixEngine\Core\Utility.h"


Fragment::Fragment()
{
	GOType = FRAGMENT;
	FragAnim = new AnimManager;
	std::vector<sf::IntRect*> Rects = AnimManager::GetSubRects(58, 63, 50, 8, 0, 0);
	FragIndex = FragAnim->AddAnim(Rects, 32);
	FragSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets\\GraphicalAssets\\FragmentSprite.png"));
	FragSprite->setTextureRect(*Rects[0]);
	CollisionRef = FragSprite;
	setPosition(50.0f, 50.0f);
}

Fragment::~Fragment()
{

}

void Fragment::setPosition(float x, float y)
{
	FragSprite->setPosition(x, y);
}

void Fragment::Update(sf::Time DeltaTime)
{

	FragAnim->Update();
	if(FragAnim->NewFrame(FragIndex))
		FragSprite->setTextureRect(*FragAnim->GetFrame(FragIndex));

}

void Fragment::HandleEvents(sf::Event EventHandle)
{

}

void Fragment::Draw(sf::RenderWindow* Window) 
{
	Window->draw(*FragSprite);
}