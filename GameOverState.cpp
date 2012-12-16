#include "GameOverState.h"

GameOverBackdrop::GameOverBackdrop(sf::RenderWindow * _ap, ResourceManager * _rm) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("gameover"));
	//Set bounds
	bounds.x = 0; 
	bounds.y = 0;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;
}

void GameOverBackdrop::update(float dt) {
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	return;
}

void GameOverBackdrop::draw(sf::RenderWindow * _ap) {
	AppPointer->Draw(sprite);
}

GameOverState::GameOverState(sf::RenderWindow * _ap, ResourceManager * _rm) : Input(_ap->GetInput()) {
	RMPointer = _rm;
	AppPointer = _ap;
	eng.setAppPointer(_ap);
	name = "GameOver";
	eng.addGenObj(new GameOverBackdrop(_ap, _rm));
	return;
}

void GameOverState::init() {
	return;
}

void GameOverState::onSwitch() {
	AppPointer->SetView(AppPointer->GetDefaultView());
	return;
}

void GameOverState::update(float dt){
	eng.updateAllGenObj(dt);
	//if(Input.IsKeyDown(sf::Key::Space)) {
	if(Input.IsKeyDown(sf::Key::Return)) {
		switchName = "Title";
	}
	return;
}

void GameOverState::draw() {
	eng.drawAllGenObj();
	return;
}



		
