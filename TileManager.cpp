#include "TileManager.h"

Tile::Tile(int x, int y, ResourceManager * _rm) {
	bounds.x = x;
	bounds.y = y;
	bounds.h = SIZE;
	bounds.w = SIZE;
	
	setZOrder(40);
	
	sprite.SetImage(*_rm->getImage("tile"));
	return;
}

void Tile::update(float dt) {
	bounds.x += dt*20;
	bounds.y += dt*20;
	
	sprite.SetX((int)bounds.x);
	sprite.SetY((int)bounds.y);
	return;
}

void Tile::draw(sf::RenderWindow * _ap) {
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


