#include "MapGenerator.h"
#include "SFML/Graphics/Color.hpp"
#include <cstdlib>
#include <ctime>

MapGenerator::MapGenerator() {

}

MapGenerator::~MapGenerator() {

}

std::vector<BSPNode*> MapGenerator::getRooms() {
	return this->rooms;
}

Map* MapGenerator::GenerateMap(int w, int h, int depth) {
	srand(time(NULL));

	Map* result = new Map(w, h);

	// Create an initialize the root dungeon node.
	BSPNode* dungeon = new BSPNode();
	this->rootNode = dungeon;

	dungeon->row = 0;
	dungeon->column = 0;
	dungeon->width = w;
	dungeon->height = h;

	// Recursively split the dungeon into halves until the specified depth is reached.
	int currentDepth = 0;
	if(currentDepth < depth) this->SplitNode(dungeon, currentDepth, depth);

	// Place rooms within each node in the dungeon tree.
	this->CreateRooms(result);

	// Connect the rooms in the dungeon.
	this->ConnectRooms(result, dungeon);

	return result;
}

void MapGenerator::SplitNode(BSPNode* node, int currentDepth, int maxDepth) {
	// Split the node by dividing the room in half, one half for the A node, and one for the B node.
	node->A = new BSPNode();
	node->B = new BSPNode();

	// Determines if the split will be horizontal or vertical.
	bool hSplit = ((node->width == node->height)?(((rand() % 100) + 1) >= 40):(node->height > node->width));

	// Division line should be between the 30% and 70% mark within the node.
	// For example: In a room width 10, the division line should be between the 3rd and 7th tiles.
	if(hSplit) {
		// Split the node horizontally.
		int min = (int)(0.3 * node->height);
		int max = (int)(0.6 * node->height);
		int rowLine = ((rand() % (max - min + 1)) + min);

		node->A->row = node->row;
		node->A->column = node->column;
		node->A->width = node->width;
		node->A->height = (((node->A->row + rowLine) + 1) - node->A->row);

		node->B->row = (node->A->row + (rowLine + 1));
		node->B->column = node->column;
		node->B->width = node->width;
		node->B->height = (node->height - node->A->height);
	} else {
		// Split the node vertically.
		int min = (int)(0.3 * node->width);
		int max = (int)(0.6 * node->width);
		int colLine = ((rand() % (max - min + 1)) + min);

		node->A->row = node->row;
		node->A->column = node->column;
		node->A->width = (((node->A->column + colLine) + 1) - node->A->column);
		node->A->height = node->height;

		node->B->row = node->row;
		node->B->column = (node->A->column + (colLine + 1));
		node->B->width = (node->width - node->A->width);
		node->B->height = node->height;
	}

	// If not at maximum depth, split again on both inner nodes.
	if(currentDepth < maxDepth) {
		this->SplitNode(node->A, (currentDepth + 1), maxDepth);
		this->SplitNode(node->B, (currentDepth + 1), maxDepth);
	} else {
		// Otherwise, add the two nodes to the list of nodes to create rooms for.
		this->rooms.push_back(node->A);
		this->rooms.push_back(node->B);
	}
}

void MapGenerator::CreateRooms(Map* map) {
	// Create a random sized rectangle room within each node.
	
	// Loop through all the created rooms.
	for(int i = 0; i < this->rooms.size(); i++) {
		BSPNode* node = this->rooms[i];

		// Get a random width and height in the range of the size of the node room.
		int minWidth = (int)(node->width * 0.5);
		int width = (rand() % (node->width - minWidth + 1)) + minWidth;
		int minHeight = (int)(node->height * 0.5);
		int height = (rand() % (node->height - minHeight + 1)) + minHeight;

		// Get the origin point based on the width and height.
		int minX = node->column;
		int maxX = (node->column + node->width) - width;
		int originX = (rand() % (maxX - minX + 1)) + minX;

		int minY = node->row;
		int maxY = (node->row + node->height) - height;
		int originY = (rand() % (maxY - minY + 1)) + minY;

		// Set the type of all tiles in the created room.
		for(int row = originY; row < (originY + height); row++) {
			for(int col = originX; col < (originX + width); col++) {
				map->GetTile(row, col)->SetType(Tile::REGULAR_TYPE);
			}
		}

		// Change the node's properties to contain the created room's dimensions.
		node->row = originY;
		node->column = originX;
		node->width = width;
		node->height = height;
	}
}

void MapGenerator::ConnectRooms(Map* map, BSPNode* parent) {
	// Start at the top node and connect each leaf to its sibling, and then recurse on each leaf.
	BSPNode* A = parent->A;
	BSPNode* B = parent->B;

	// Get the center points for both rooms.
	int aCX = (A->column + A->width) - (A->width / 2);
	int aCY = (A->row + A->height) - (A->height / 2);

	int bCX = (B->column + B->width) - (B->width / 2);
	int bCY = (B->row + B->height) - (B->height / 2);

	// Connect the two points on the X-axis.
	for(int startX = aCX; startX != bCX; startX += ((aCX < bCX)?1:-1)) {
		map->GetTile(aCY, startX)->SetType(Tile::REGULAR_TYPE);
	}
	// Connect the two points on the Y-axis.
	for(int startY = aCY; startY != bCY; startY += ((aCY < bCY)?1:-1)) {
		map->GetTile(startY, bCX)->SetType(Tile::REGULAR_TYPE);
	}

	if(A->A != NULL && A->B != NULL) ConnectRooms(map, A);
	if(B->A != NULL && B->B != NULL) ConnectRooms(map, B);
}