#include "TitleState.h"
TitleState::TitleState(const sf::Input & _input) : Input(_input) {
	//RMPointer has not been set yet at this point!
	name = "Title";
	return;
}

void TitleState::init() {
	try {
		titleSprite.SetImage(*RMPointer->getImage("title"));
		pointerSprite.SetImage(*RMPointer->getImage("pointer"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
	eng.setAppPointer(AppPointer);
	sf::Sprite * tmp = new sf::Sprite;
	tmp->SetImage(*RMPointer->getImage("pointer"));
	mouse = eng.makeAndAddObj(tmp, 20);
}

void TitleState::update(float dt) {
	mouse->sprite->SetX(Input.GetMouseX());
	mouse->sprite->SetY(Input.GetMouseY());
	std::cout << dt << std::endl;
	pointerSprite.SetX(Input.GetMouseX());
	pointerSprite.SetY(Input.GetMouseY());
	if (Input.IsMouseButtonDown(sf::Mouse::Left)) {
		switchName = "Game";
	}
}

void TitleState::draw() {
	//AppPointer->Draw(titleSprite);
	//AppPointer->Draw(pointerSprite);
	AppPointer->Clear();
	eng.drawAll();
	return;
}
