#include "GameState.h"
GameState::GameState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()), tm(_ap, _rm) {
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
	if (Input.IsKeyDown(sf::Key::Space)) {
		eng.addGenObj(tm.makeATile());
	}
	return;
}

void GameState::draw() {
	eng.drawAllGenObj();
	return;
}
