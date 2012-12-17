#include "GameState.h"
#include "Player.h"


//For rand() func
#include <ctime>
#include <cstdlib>

#include "Enemies.h"

GameState::GameState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()), tm(_ap, _rm) {
	//RMPointer has not been set yet at this point!
	RMPointer = _rm;
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
	std::cout << "HKDJFSK";
	//Set view things
	view.SetFromRect(sf::FloatRect(0, 0, 500, 400));
	srand(time(NULL));
	
	eng.addGenObj(new FPSDisplay);
	playerptr = tm.generateMap(&eng);
	//You can add objects twice to have them doubly updated (BAD!)
	//eng.addGenObj(playerptr);
}

void GameState::init() {
	//tm.generateTiles(&eng);
	return;
}

void GameState::onSwitch() {
	AppPointer->SetView(view);
}

void GameState::onSwitchOut() {
	return;
}

void GameState::update(float dt) {
	//sf::Vector2 pos = sf::Vector2<int>(playerptr->bounds.x, playerptr->bounds.y);
	/*
	if (Input.IsKeyDown(sf::Key::Space)) {
		tm.generateTiles(&eng);
		//eng.addGenObj(tm.makeATile(2, 2));
	}*/
	
	if (Input.IsKeyDown(sf::Key::Return)) {
		view.Move(rand()%10, rand()%10);
	}
	eng.updateAllGenObj(dt);
	
	//if(rand()%10==0) {
		if (Input.IsKeyDown(sf::Key::E)) {
		eng.addGenObj(new FallingBlock(AppPointer, RMPointer, &eng));
		}
	//}
	if (Input.IsKeyDown(sf::Key::S)) {
		eng.addGenObj(new SecBot(AppPointer, RMPointer, &eng, playerptr));
	}
	 
	if (Input.IsKeyDown(sf::Key::K)) {
		playerptr->health = 0;
	}
	//This needs to be below updateAllGenObj so that it gets the latest player coords
	BoundingBox temp_bb = playerptr->getBounds();
	view.SetCenter(sf::Vector2<float>(temp_bb.x, temp_bb.y));
	return;
}

void GameState::draw() {
	eng.drawAllGenObj();
	return;
}
