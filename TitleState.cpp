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
}

void TitleState::update(float dt) {
	DrawObj * temp = new DrawObj;
	sf::Sprite *tempsp = new sf::Sprite;
	tempsp->SetImage(*RMPointer->getImage("sat1"));
	temp->sprite = tempsp;
	temp->zorder = 10;
	temp->destroy = false;
	
	std::cout << dt << std::endl;
	pointerSprite.SetX(Input.GetMouseX());
	pointerSprite.SetY(Input.GetMouseY());
	if (Input.IsMouseButtonDown(sf::Mouse::Left)) {
		switchName = "Game";
	}
	if (Input.IsKeyDown(sf::Key::Space)) {
		eng.addDrawObj(temp);
	}
}

void TitleState::draw() {
	//AppPointer->Draw(titleSprite);
	//AppPointer->Draw(pointerSprite);
	eng.drawAll();
	return;
}
