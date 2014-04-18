#ifndef SFMLAPP_H
#define SFMLAPP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/System/Time.hpp"
#include "TextureManager.h"
#include "Map.h"
#include "MapGenerator.h"
#include "Entity.h"

class SFMLApp {
	private:
		bool running;
		bool viewKeys[4];
		bool moveKeys[4];
		sf::RenderWindow* window;
		sf::View* viewport;
		TextureManager textureManager;

		Map* currentMap;
		Entity* player;
		bool moved;

	public:
		static const int WINDOW_WIDTH = 1024;
		static const int WINDOW_HEIGHT = 768;

		SFMLApp();
		virtual ~SFMLApp();

		// SFML Specific
		bool Init(const char * title = "SFML App");

		void HandleEvent(sf::Event* event);
		void Update(sf::Time elapsedTime);
		void Render();

		void Cleanup();

		int Execute();

		void LoadTextures();

		// Other
		void SetViewportFocus(sf::Vector2f center);
		void SetViewportZoom(float factor);
		bool CheckValidMove(int rOff, int cOff);
};

#endif