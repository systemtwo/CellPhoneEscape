#include "GameState.h"
#include "Player.h"
GameState::GameState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()), tm(_ap, _rm) {
	//RMPointer has not been set yet at this point!
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
	
	eng.addGenObj(new FPSDisplay);
	eng.addGenObj(new Player(AppPointer, _rm));
}

void GameState::init() {
	//tm.generateTiles(&eng);
	return;
}

void GameState::update(float dt) {
	if (Input.IsKeyDown(sf::Key::Space)) {
		tm.generateTiles(&eng);
		//eng.addGenObj(tm.makeATile(2, 2));
	}
	eng.updateAllGenObj(dt);
	return;
}

void GameState::draw() {
	eng.drawAllGenObj();
	return;
}
