#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;

	// Set the size of the tiles vector and initialize the rows of tiles.
	this->tiles.resize(h);
	for(int r = 0; r < h; r++) {
		for(int c = 0; c < w; c++) {
			this->tiles[r].push_back(new Tile(((c * Tile::TILE_SIZE) + (Tile::TILE_SIZE / 2)), ((r * Tile::TILE_SIZE) + (Tile::TILE_SIZE / 2)), Tile::WALL_TYPE, false));
		}
	}
}

Map::~Map() {

}

int Map::GetWidth() {
	return this->width;
}

int Map::GetHeight() {
	return this->height;
}

Tile* Map::GetTile(int row, int column) {
	if(((row >= 0) && (row < this->height)) && ((column >= 0) && (column < this->width))) return this->tiles[row][column];
	else return NULL;
}

void Map::DrawTiles(sf::RenderWindow* window) {
	for(int r = 0; r < this->height; r++) {
		for(int c = 0; c < this->width; c++) {
			this->tiles[r][c]->Draw(window);
		}
	}
}