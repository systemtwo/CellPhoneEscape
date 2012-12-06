#include "GameState.h"
GameState::GameState(sf::RenderWindow * _ap) : Input(_ap->GetInput()), player(400,400,200) {
	//RMPointer has not been set yet at this point!
	AppPointer = _ap;
	name = "Game";
}

void GameState::init() {
	try {
		backgroundSprite.SetImage(*RMPointer->getImage("rubix"));
		pointerSprite.SetImage(*RMPointer->getImage("pointer"));
		sat1Sprite.SetImage(*RMPointer->getImage("sat1"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
	time = 0;

	
	return;
}

void GameState::update(float dt) {
	return;
}

void GameState::draw() {
	//AppPointer->Draw(backgroundSprite);
	//AppPointer->Draw(pointerSprite);
	//AppPointer->Draw(sat1Sprite);
	return;
}
