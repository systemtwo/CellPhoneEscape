#include "GameState.h"
GameState::GameState(sf::RenderWindow * _ap) : Input(_ap->GetInput()) {
	//RMPointer has not been set yet at this point!
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
}

void GameState::init() {
	/*
	try {
		backgroundSprite.SetImage(*RMPointer->getImage("rubix"));
		pointerSprite.SetImage(*RMPointer->getImage("pointer"));
		sat1Sprite.SetImage(*RMPointer->getImage("sat1"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
	time = 0;
	*/
	eng.addGenObj(new FPSDisplay);
	return;
}

void GameState::update(float dt) {
	eng.updateAllGenObj(dt);
	return;
}

void GameState::draw() {
	//AppPointer->Draw(backgroundSprite);
	//AppPointer->Draw(pointerSprite);
	//AppPointer->Draw(sat1Sprite);
	eng.drawAllGenObj();
	return;
}
