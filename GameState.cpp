#include "GameState.h"
#include "Player.h"
#include "Enemies.h"
GameState::GameState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()), tm(_ap, _rm) {
	//RMPointer has not been set yet at this point!
	RMPointer = _rm;
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
	
	//Set view things
	view.SetFromRect(sf::FloatRect(0, 0, 400, 300));
	
	
	eng.addGenObj(new FPSDisplay);
	playerptr = new Player(AppPointer, _rm, &eng);
	eng.addGenObj(playerptr);
}

void GameState::init() {
	//tm.generateTiles(&eng);
	return;
}

void GameState::onSwitch() {
	AppPointer->SetView(view);
}

void GameState::update(float dt) {
	//sf::Vector2 pos = sf::Vector2<int>(playerptr->bounds.x, playerptr->bounds.y);
	BoundingBox temp_bb = playerptr->getBounds();
	view.SetCenter(sf::Vector2<float>(temp_bb.x, temp_bb.y));
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
