#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <string>


struct TextureObject
{
	public:
		sf::Texture* Texture;
		bool bPersistent;
		std::string Path;
};

class ImageManager
{
	public:
		static sf::Texture* RequestTexture(std::string Path, bool bPersistent = false);
		static void ClearCache();
		static void ClearPersistent();

	private:

		static std::vector<TextureObject*> Textures;
};