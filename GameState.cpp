#include "GameState.h"
GameState::GameState(const sf::Input & _input) : Input(_input), player(400,400,200) {
	//RMPointer has not been set yet at this point!
	name = "Game";
	

}

void GameState::init() {
	std::cout << "RMPointer Address at TS: " << RMPointer << std::endl;
	try {
		backgroundSprite.SetImage(*RMPointer->getImage("rubix"));
		pointerSprite.SetImage(*RMPointer->getImage("pointer"));
		sat1Sprite.SetImage(*RMPointer->getImage("sat1"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
	time = 0;
}

void GameState::update(float dt) {
	double rad;
	double x = 0, y = 0;
	double orbitradius = 100;
	double centerx = 200;
	double centery = 200;
	int orbitspeed = 2;
	
	//player1 (400,400,200);
	
	//Get input
	/*
	if (Input.IsKeyDown(sf::Key::Left)) {
		std::cout << left;	
	} else if (Input.IsKeyDown(sf::Key::Right)) {
		std::cout << right;
	} else if (Input.IsKeyDown(sf::Key::Up)) {
		std::cout << up;
	} else if (Input.IsKeyDown(sf::Key::Down)) {
		std::cout << down;
	}*/
	
	if (Input.IsKeyDown(sf::Key::Up)) {
		player.turnOnEngine();
	} else if (!Input.IsKeyDown(sf::Key::Up)) {
		player.turnOffEngine();
	}
	
	if (Input.IsKeyDown(sf::Key::Left)) {
		player.rotateSatellite(left);
	} else if (Input.IsKeyDown(sf::Key::Right)){
		player.rotateSatellite(right);
	}
	player.calcForces();
	player.calcSpeeds();
	player.updateSatelliteRotation();
	player.updatePosition();

	pointerSprite.SetX(Input.GetMouseX());
	pointerSprite.SetY(Input.GetMouseY());
	
	rad = time*PI/180;
	
	y = (sin(rad) * orbitradius) + centery;
	x = (cos(rad) * orbitradius) + centerx;
	time += orbitspeed;
	
	if (time > 360) {
		time = 0;
	}
	
	sat1Sprite.SetRotation(-time);
	sat1Sprite.SetY(y);
	sat1Sprite.SetX(x);
	
	
}

void GameState::draw() {
	AppPointer->Draw(backgroundSprite);
	AppPointer->Draw(pointerSprite);
	AppPointer->Draw(sat1Sprite);
	return;
}
