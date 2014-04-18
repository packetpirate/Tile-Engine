#include "Tile.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"

const float Tile::TILE_SIZE = 64.0f;

Tile::Tile(float cx, float cy, int type, bool traversable) {
	this->cx = cx;
	this->cy = cy;
	this->type = type;
	this->traversable = traversable;

	this->shape = sf::RectangleShape(sf::Vector2f(Tile::TILE_SIZE, Tile::TILE_SIZE));
	this->shape.setPosition(sf::Vector2f(((cx - (Tile::TILE_SIZE / 2))), ((cy - (Tile::TILE_SIZE / 2)))));
	this->shape.setFillColor((type == Tile::WALL_TYPE)?(sf::Color::Black):(sf::Color::White));
}

Tile::~Tile() {

}

sf::Vector2f Tile::GetCenter() {
	return sf::Vector2f(this->cx, this->cy);
}

int Tile::GetType() {
	return this->type;
}

void Tile::SetType(int type) {
	this->type = type;
	switch(type) {
		case Tile::WALL_TYPE: {
			// Walls
			this->traversable = false;
			this->SetColor(sf::Color::Black);
		}
		case Tile::REGULAR_TYPE: {
			// Regular traversable tiles.
			this->traversable = true;
			this->SetColor(sf::Color::White);
		}
	}
}

void Tile::SetColor(sf::Color color) {
	this->shape.setFillColor(color);
}

bool Tile::IsTraversable() {
	return this->traversable;
}

void Tile::Draw(sf::RenderWindow* window) {
	window->draw(this->shape);
}