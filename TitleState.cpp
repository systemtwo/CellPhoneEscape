#include "TitleState.h"
TitleState::TitleState(const sf::Input & _input) : Input(_input) {
	//RMPointer has not been set yet at this point!
	name = "Title";
	return;
}

void TitleState::init() {
	try {
		titleSprite.SetImage(*RMPointer->getImage("title"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
	eng.setAppPointer(AppPointer);
	sf::Sprite * tmp = new sf::Sprite;
	tmp->SetImage(*RMPointer->getImage("pointer"));
	mouse = eng.makeAndAddObj(tmp, 20);
}

void TitleState::update(float dt) {
	int mouseXShift = mouse->sprite->GetSize().x;
	int mouseYShift = mouse->sprite->GetSize().y;
	mouse->sprite->SetX(Input.GetMouseX()-(mouseXShift/2));
	mouse->sprite->SetY(Input.GetMouseY()-(mouseYShift/2));
	std::cout << dt << std::endl;
	if (Input.IsMouseButtonDown(sf::Mouse::Left)) {
		switchName = "Game";
	}
}

void TitleState::draw() {
	eng.drawAll();
	return;
}
