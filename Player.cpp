#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(sf::RenderWindow * _ap, ResourceManager * _rm) : input(_ap->GetInput()) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("player"));
	sprite.SetX(0);
	sprite.SetY(0);
	
	setZOrder(10);
	return;
}

void Player::update(float dt) {
	int speed = 40;
	if (input.IsKeyDown(sf::Key::Left)) {
		sprite.Move(-dt*speed, 0);
	}
	if (input.IsKeyDown(sf::Key::Right)) {
		sprite.Move(dt*speed, 0);
	}
	if (input.IsKeyDown(sf::Key::Up)) {
		sprite.Move(0, -dt*speed);
	}
	if (input.IsKeyDown(sf::Key::Down)) {
		sprite.Move(0, dt*speed);
	}
	return;
}

void Player::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}
