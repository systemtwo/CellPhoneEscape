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
	
	return;
}

void GameOverState::init() {
	return;
}

void GameOverState::onSwitch() {
	AppPointer->SetView(AppPointer->GetDefaultView());
	
	sf::Image * i10 = new sf::Image;
	i10->LoadFromFile("images/GameOver.png");
	RMPointer->storeImage(i10, "gameover");
	eng.addGenObj(new GameOverBackdrop(AppPointer, RMPointer));
	return;
}

void GameOverState::onSwitchOut() {
	RMPointer->deleteImage("gameover");
	eng.deleteAllGenObj();
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



		
