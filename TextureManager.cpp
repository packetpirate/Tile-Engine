#include "TextureManager.h"
#include <cstdlib>

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {

}

void TextureManager::AddTexture(const char * filename, const char * identifier) {
	sf::Texture texture;
	if(!texture.loadFromFile(filename)) {
		printf("There was an error loading the texture from the file: %s", filename);
	} else {
		this->textures[identifier] = texture;
	}
}

sf::Texture* TextureManager::GetTexture(const char * identifier) {
	return &(this->textures[identifier]);
}