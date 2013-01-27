#include "Fragment.h"
#include "PhoenixEngine\Core\Utility.h"


Fragment::Fragment()
{
	GOType = FRAGMENT;
	std::vector<sf::IntRect*> Rects;
	FragAnim = new AnimManager;
	for (unsigned int i = 0; i < 50; i++)
	{
		Rects.push_back(nullptr);
		std::string path;
		path = Util::BuildString("Assets/GraphicalAssets/Fragments/Fragments00%02d.png", i);
		FragTexture.push_back(ImageManager::RequestTexture(path));
	}
	FragIndex = FragAnim->AddAnim(Rects, 32);
	FragSprite = new sf::Sprite(*FragTexture[0]);
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
		FragSprite->setTexture(*FragTexture[FragAnim->CurFrame(FragIndex)]);

}

void Fragment::HandleEvents(sf::Event EventHandle)
{

}

void Fragment::Draw(sf::RenderWindow* Window) 
{
	Window->draw(*FragSprite);
}