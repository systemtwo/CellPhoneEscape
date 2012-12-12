#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng) : input(_ap->GetInput()) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("player"));

	setZOrder(10);
	
	eng = _eng;
	//Set bounds
	bounds.x = 100;
	bounds.y = 100;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;

	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	jumping = false;
	jumpReady = true;
	jumpHeight = 0;
	
	return;
}

void Player::update(float dt) {
	int speed = 40;
	
	
	CollisionObj co = eng->detectCollisions(bounds, this);
	std::cout << co.collType;
	if (co.collType != BOTTOM) {
		bounds.y += dt* 100;
	}else{
		jumpReady=true;
	}
	
	if (input.IsKeyDown(sf::Key::Left)) {
		bounds.x -= dt*speed;
		//sprite.Move(-dt*speed, 0);
	}
	if (input.IsKeyDown(sf::Key::Right)) {
		bounds.x += dt*speed;
		//sprite.Move(dt*speed, 0);
	}
	
	if (input.IsKeyDown(sf::Key::Up)) {
		if (jumpReady==true) {
		std::cout<<std::endl<<jumpReady<<std::endl<<jumping<<std::endl;
			jumping=true;
			jumpHeight=0;
			jumpReady=false;
		std::cout<<std::endl<<jumpReady<<std::endl<<jumping<<std::endl;
		}
		//sprite.Move(0, -dt*speed);
	} else {
		jumping=false;
	}
	if(jumping==true)
	{
		if ((co.collType != TOP)&&(jumpHeight<maxJumpHeight)) {
			bounds.y -= 10;
			jumpHeight += 10;
		} else {
			jumping=false;
		}
	}
	
	
	if (input.IsKeyDown(sf::Key::Down)) {
		bounds.y += dt*speed;
		//sprite.Move(0, dt*speed);
	}
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	
	
	return;
}

void Player::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}
