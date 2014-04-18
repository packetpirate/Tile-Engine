#include "Entity.h"
#include "Tile.h"

Entity::Entity(int row, int col, sf::Vector2f center, bool focus) {
	this->row = row;
	this->column = col;
	this->center = center;
	this->focus = focus;

	this->shape = sf::RectangleShape(sf::Vector2f((Tile::TILE_SIZE - 2), (Tile::TILE_SIZE - 2)));
	this->shape.setPosition(sf::Vector2f(((this->center.x - (Tile::TILE_SIZE / 2) + 1)), ((this->center.y - (Tile::TILE_SIZE / 2) + 1))));
	this->shape.setFillColor(sf::Color::Red);
}

Entity::~Entity() {

}

int Entity::GetRow() {
	return this->row;
}

int Entity::GetColumn() {
	return this->column;
}

sf::Vector2f Entity::GetCenter() {
	return this->center;
}

void Entity::Move(int r, int c, sf::View* viewport) {
	this->row += r;
	this->column += c;
	this->center.x += (c * Tile::TILE_SIZE);
	this->center.y += (r * Tile::TILE_SIZE);
	this->shape.setPosition(sf::Vector2f((this->center.x - (Tile::TILE_SIZE / 2) + 1), (this->center.y - (Tile::TILE_SIZE / 2) + 1)));
	if(this->focus) viewport->setCenter(this->center);
}

void Entity::Draw(sf::RenderWindow* window) {
	window->draw(this->shape);
}