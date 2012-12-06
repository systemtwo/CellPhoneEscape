#include "GameState.h"
GameState::GameState(sf::RenderWindow * _ap) : Input(_ap->GetInput()) {
	//RMPointer has not been set yet at this point!
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
}

void GameState::init() {
	eng.addGenObj(new FPSDisplay);
	return;
}

void GameState::update(float dt) {
	eng.updateAllGenObj(dt);
	return;
}

void GameState::draw() {
	eng.drawAllGenObj();
	return;
}
