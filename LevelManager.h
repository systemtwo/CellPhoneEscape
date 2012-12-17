#ifndef TM_H
#define TM_H

#include <vector>
#include <SFML/graphics.hpp>
#include "Engine.h"
#include "ResourceManager.h"
#include "Player.h"

const int TILE_SIZE = 32;

class Tile : public GenericObj {
	public:
		Tile(int x, int y, ResourceManager * _rm, int type);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		int type;
		//BoundingBox bounds;
		//int zorder;
	private:
		sf::Sprite sprite;
		const static int SIZE = 33;
};


class LevelManager {
	public:
		LevelManager(sf::RenderWindow * _ap, ResourceManager * _rm);
		Player * generateMap(Engine * eng);
		Tile * makeATile(int i, int j);
	private:
		sf::RenderWindow * AppPointer;
		ResourceManager * RMPointer;
		int level;
};



#endif
