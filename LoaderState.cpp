#include "LoaderState.h"
LoaderState::LoaderState() {
	//RMPointer has not been set yet at this point!
	name = "Loader";
}

void LoaderState::init() {
	sf::Image * i1 = new sf::Image;
	//Don't reuse these to load other images (they are the actual image resource sprites link to)
	i1->LoadFromFile("images/newtitle.png");
	RMPointer->storeImage(i1, "title");

	sf::Image * i2 = new sf::Image;
	i2->LoadFromFile("images/icon.png");
	RMPointer->storeImage(i2, "player");
	
	sf::Image * i3 = new sf::Image;
	i3->LoadFromFile("images/tile2.png");
	RMPointer->storeImage(i3, "tile2");
	
	sf::Image * i4 = new sf::Image;
	i4->LoadFromFile("images/sms_cat.png");
	RMPointer->storeImage(i4, "enemy");
	
	sf::Image * i5 = new sf::Image;
	i5->LoadFromFile("images/binary.png");
	RMPointer->storeImage(i5, "binary");
	
	sf::Image * i6 = new sf::Image;
	i6->LoadFromFile("images/tile.png");
	RMPointer->storeImage(i6, "tile1");
}

void LoaderState::update() {
	//This state does nothing but load resources and display a screen that says "Loading"
	return;
}

void LoaderState::draw() {
	//AppPointer->Draw(loaderSprite);
	return;
}
