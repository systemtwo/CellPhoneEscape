#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(sf::RenderWindow * _ap, ResourceManager * _rm) : input(_ap->GetInput()) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("player"));

	setZOrder(10);
	//Set bounds
	bounds.x = 100;
	bounds.y = 100;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;

	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
		
	return;
}

void Player::update(float dt) {
	int speed = 40;
	if (input.IsKeyDown(sf::Key::Left)) {
		bounds.x -= dt*speed;
		//sprite.Move(-dt*speed, 0);
	}
	if (input.IsKeyDown(sf::Key::Right)) {
		bounds.x += dt*speed;
		//sprite.Move(dt*speed, 0);
	}
	if (input.IsKeyDown(sf::Key::Up)) {
		bounds.y -= dt*speed;
		//sprite.Move(0, -dt*speed);
	}
	if (input.IsKeyDown(sf::Key::Down)) {
		bounds.y += dt*speed;
		//sprite.Move(0, dt*speed);
	}
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	//sprite.Move(0,1);
	return;
}

void Player::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}
