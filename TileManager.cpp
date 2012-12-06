#include "TileManager.h"

Tile::Tile(int x, int y, ResourceManager * _rm) {
	bounds.x = x;
	bounds.y = y;
	bounds.h = SIZE;
	bounds.w = SIZE;
	
	sprite.SetImage(*_rm->getImage("tile"));
	return;
}

void Tile::update(float dt) {
	sprite.SetX(bounds.x+ 100);
	sprite.SetY(bounds.y+ 100);
	
	return;
}

void Tile::draw(sf::RenderWindow * _ap) {
	std::cout << "I am called?" << std::endl;
	_ap->Draw(sprite);
	return;
}


TileManager::TileManager(sf::RenderWindow * _ap, ResourceManager * _rm) {
	AppPointer = _ap;
	RMPointer = _rm;
	return;
}

void TileManager::generateTiles() {
	return;
}

Tile * TileManager::makeATile() {
	return new Tile(0,0, RMPointer);
}


