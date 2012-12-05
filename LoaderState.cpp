#include "LoaderState.h"
LoaderState::LoaderState(const sf::Input & _input) : Input(_input) {
	//RMPointer has not been set yet at this point!
	name = "Loader";
}

void LoaderState::init() {
	sf::Image * i1 = new sf::Image;
	sf::Image * i2 = new sf::Image;
	sf::Image * i3 = new sf::Image;
	sf::Image * i4 = new sf::Image;
	
	i1->LoadFromFile("images/title.png");
	i2->LoadFromFile("images/ch.png");
	i3->LoadFromFile("images/a.jpg");
	i4->LoadFromFile("images/sat1.png"); //Don't reuse these to load other images (they are the actual image resource sprites link to)
	
	RMPointer->storeImage(i2, "pointer");
	RMPointer->storeImage(i1, "title");
	RMPointer->storeImage(i3, "rubix");
	RMPointer->storeImage(i4, "sat1");
}

void LoaderState::update() {
	//This state does nothing but load resources and display a screen that says "Loading"
}

void LoaderState::draw() {
	//AppPointer->Draw(loaderSprite);
	return;
}
