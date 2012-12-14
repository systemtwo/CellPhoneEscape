#include "GameState.h"
#include "Player.h"

//For rand() func
#include <ctime>
#include <cstdlib>
GameState::GameState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()), tm(_ap, _rm) {
	//RMPointer has not been set yet at this point!
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "Game";
	
	//Set view things
	view.SetFromRect(sf::FloatRect(0, 0, 400, 300));
	srand(time(NULL));
	
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
	view.SetCenter(sf::Vector2<float>(playerptr->bounds.x, playerptr->bounds.y));
	if (Input.IsKeyDown(sf::Key::Space)) {
		tm.generateTiles(&eng);
		//eng.addGenObj(tm.makeATile(2, 2));
	}
	
	if (Input.IsKeyDown(sf::Key::Return)) {
		view.Move(rand()%10, rand()%10);
	}
	eng.updateAllGenObj(dt);
	return;
}

void GameState::draw() {
	eng.drawAllGenObj();
	return;
}
