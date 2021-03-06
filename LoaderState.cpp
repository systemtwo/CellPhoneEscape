#include "LoaderState.h"
LoaderState::LoaderState() {
	//RMPointer has not been set yet at this point!
	name = "Loader";
}

void LoaderState::init() {
	//Now this should only be used for assets that are used in multiple states
	
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
	i6->LoadFromFile("images/circuit.png");
	RMPointer->storeImage(i6, "tile1");
	
	sf::Image * i7 = new sf::Image;
	i7->LoadFromFile("images/arrgav.png");
	RMPointer->storeImage(i7, "arrgav");
	
	sf::Image * i8 = new sf::Image;
	i8->LoadFromFile("images/uparrow.png");
	RMPointer->storeImage(i8, "uparrow");
	
	sf::Image * i9 = new sf::Image;
	i9->LoadFromFile("images/background.png");
	RMPointer->storeImage(i9, "background");
	
	sf::Image * i10 = new sf::Image;
	i10->LoadFromFile("images/VertLaser.png");
	RMPointer->storeImage(i10, "laserV");

}

void LoaderState::update() {
	//This state does nothing but load resources and display a screen that says "Loading"
	return;
}

void LoaderState::draw() {
	//AppPointer->Draw(loaderSprite);
	return;
}
