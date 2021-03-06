#include "LevelManager.h"
#include <fstream>
#include <iostream>
#include <cstring>
//#include "Player.h"

using namespace std;


Tile::Tile(int x, int y, ResourceManager * _rm, int _type) {
	//Note x, y are grid coordinates NOT Global game screen coords
	bounds.x = x*SIZE;
	bounds.y = y*SIZE;
	bounds.h = SIZE;
	bounds.w = SIZE;
	
	setZOrder(40);
	
	char fname[100];
	char tilenum[25];
	itoa(_type, tilenum, 10);
	strcpy(fname, "tile");
	strcat(fname, tilenum);
	sprite.SetImage(*_rm->getImage(fname)); //Tile manager shuold handle this
	sprite.SetX((int)bounds.x);
	sprite.SetY((int)bounds.y);
	
	name = "tile";
	type = _type;
	return;
}

void Tile::update(float dt) {
	return;
}

void Tile::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}


LevelManager::LevelManager(sf::RenderWindow * _ap, ResourceManager * _rm) {
	AppPointer = _ap;
	RMPointer = _rm;
	return;
}

Player * LevelManager::generateMap(Engine * eng) {
	ifstream in;
	int height = 0;
	int width  = 0;
	int tileType = 0;
	
	in.open("leveldata/lv1.txt");
	Player * player;
	
	in >> width >> height;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			in >> tileType;
			if (tileType == -1) {
				cout << "Hit -1" << endl;
				player = new Player(AppPointer, RMPointer, eng, j*TILE_SIZE, i*TILE_SIZE);
				eng->addGenObj(player);
			}else if (tileType != 0) {
				eng->addGenObj(new Tile(j,i,RMPointer, tileType));
			}
		}
	}
	cout << "CALLed";
	
	return player;
}

Tile * LevelManager::makeATile(int i, int j) {
	return new Tile(i,j, RMPointer, 1);
}


