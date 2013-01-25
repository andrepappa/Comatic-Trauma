#include "ImageManager.h"

#include <iostream>
#include <string>
#include "Utility.h"

std::vector<TextureObject*> ImageManager::Textures;

sf::Texture* ImageManager::RequestTexture(std::string Path, bool bPersistent)
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		if(Textures[i]->Path == Path)
		{
			return Textures[i]->Texture;
		}
	}

	TextureObject* TexObj = new TextureObject();
	sf::Texture* Tex = new sf::Texture();
	if(Tex->loadFromFile(Path))
		Util::msgNote(Util::BuildString("New image loaded: %s", Path.c_str()));
	else
		Util::msgErr(Util::BuildString("Error loading image: %s", Path.c_str()));
	TexObj->Texture = Tex;
	TexObj->bPersistent = bPersistent;
	TexObj->Path = Path;
	Textures.push_back(TexObj);
	return Tex;
}

void ImageManager::ClearCache()
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		if(!Textures[i]->bPersistent)
		{
			delete Textures[i]->Texture;
			delete Textures[i];
			Textures.erase(Textures.begin() + i);
		}
	}
}

void ImageManager::ClearPersistent()
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		delete Textures[i]->Texture;
		delete Textures[i];
	}
	Textures.clear();
}