#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "Map.h"
#include <vector>

struct BSPNode {
	int row, column;
	int width, height;

	BSPNode* A;
	BSPNode* B;
};

class MapGenerator {
	private:
		BSPNode* rootNode;
		std::vector<BSPNode*> rooms;

		void SplitNode(BSPNode* node, int currentDepth, int maxDepth);
		void CreateRooms(Map* map);
		void ConnectRooms(Map* map, BSPNode* parent);

	public:
		static const int MIN_NODE_SIZE = 3;

		MapGenerator();
		virtual ~MapGenerator();

		std::vector<BSPNode*> getRooms();
		Map* GenerateMap(int w, int h, int depth);
};

#endif