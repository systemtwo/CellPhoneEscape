#ifndef TM_H
#define TM_H

#include <vector>
#include <SFML/graphics.hpp>
#include "Engine.h"
class TileManager {
	public:
		void generateTiles();
		
};

class Tile {
	public:
		BoundingBox bounds;
		
	private:
		sf::Sprite tile;
		
};

#endif
