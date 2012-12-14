#include "GameState.h"
#include "Player.h"
#include "Enemies.h"
GameState::GameState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()), tm(_ap, _rm) {
	//RMPointer has not been set yet at this point!
	RMPointer = _rm;
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
	
	eng.addGenObj(new FPSDisplay);
	eng.addGenObj(new Player(AppPointer, _rm, &eng));
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
	
	if(rand()%10==0) {
		eng.addGenObj(new FallingBlock(AppPointer, RMPointer, &eng));
	}
	
	return;
}

void GameState::draw() {
	eng.drawAllGenObj();
	return;
}
