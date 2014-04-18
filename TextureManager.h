#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SFML/Graphics.hpp"
#include <map>

class TextureManager {
	private:
		std::map<const char *, sf::Texture> textures;

	public:
		TextureManager();
		virtual ~TextureManager();

		void AddTexture(const char * filename, const char * identifier);
		sf::Texture* GetTexture(const char * identifier);
};

#endif