#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <vector>

class Map {
	private:
		int width, height;
		std::vector< std::vector<Tile*> > tiles;

	public:
		Map(int w = 0, int h = 0);
		virtual ~Map();

		int GetWidth();
		int GetHeight();
		
		Tile* GetTile(int row, int column);
		void DrawTiles(sf::RenderWindow* window);
};

#endif