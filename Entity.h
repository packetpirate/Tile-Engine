#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"

class Entity {
	private:
		int row, column; // This entity's location on the map.
		sf::Vector2f center; // The X and Y location of this entity in relation to the coordinate grid.
		sf::RectangleShape shape;
		bool focus; // Does the viewport center itself on this entity?

	public:
		Entity(int row, int col, sf::Vector2f center, bool focus);
		virtual ~Entity();

		int GetRow();
		int GetColumn();
		sf::Vector2f GetCenter();

		void Move(int r, int c, sf::View* viewport);
		void Draw(sf::RenderWindow* window);
};

#endif