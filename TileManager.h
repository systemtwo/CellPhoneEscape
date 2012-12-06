#ifndef TM_H
#define TM_H

#include <vector>
#include <SFML/graphics.hpp>
#include "Engine.h"
#include "ResourceManager.h"

class Tile : public GenericObj {
	public:
		Tile(int x, int y, ResourceManager * _rm);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
		BoundingBox bounds;
		int zorder = 40;
	private:
		sf::Sprite sprite;
		const static int SIZE = 32;
};


class TileManager {
	public:
		TileManager(sf::RenderWindow * _ap, ResourceManager * _rm);
		void generateTiles();
		Tile * makeATile();
	private:
		sf::RenderWindow * AppPointer;
		ResourceManager * RMPointer;
};



#endif
