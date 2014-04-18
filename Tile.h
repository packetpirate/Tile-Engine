#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Color.hpp"

class Tile {
	private:
		float cx, cy;
		int type;
		bool traversable;

		sf::RectangleShape shape;
		sf::Sprite sprite;

	public:
		static const float TILE_SIZE;

		Tile(float cx, float cy, int type, bool traversable);
		virtual ~Tile();

		sf::Vector2f GetCenter();
		int GetType();
		void SetType(int type);

		void SetColor(sf::Color color);

		bool IsTraversable();

		void Draw(sf::RenderWindow* window);

		static const int WALL_TYPE = 0;
		static const int REGULAR_TYPE = 1;
};

#endif