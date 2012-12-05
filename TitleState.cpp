#include "TitleState.h"
TitleState::TitleState(const sf::Input & _input) : Input(_input) {
	//RMPointer has not been set yet at this point!
	name = "Title";
	

}

void TitleState::init() {
	std::cout << "RMPointer Address at TS: " << RMPointer << std::endl;
	try {
		titleSprite.SetImage(*RMPointer->getImage("title"));
		pointerSprite.SetImage(*RMPointer->getImage("pointer"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
}

void TitleState::update(float dt) {
	std::cout << dt << std::endl;
	pointerSprite.SetX(Input.GetMouseX());
	pointerSprite.SetY(Input.GetMouseY());
	if (Input.IsMouseButtonDown(sf::Mouse::Left)) {
		switchName = "Game";
	}
}

void TitleState::draw() {
	AppPointer->Draw(titleSprite);
	AppPointer->Draw(pointerSprite);
	return;
}
