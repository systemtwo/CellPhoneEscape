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

	
	name = "player";

	
	return;
}

void Player::update(float dt) {
	int speed = 40;
	
	
	CollisionObj co = eng->detectCollisions(bounds, this);
	std::cout << co.collD;
	if (co.collD == false) {
		bounds.y += dt* 100;
	}else{
		jumpReady=true;
		jumping = false;
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
<<<<<<< HEAD
		if (jumpReady==true) {
		std::cout<<std::endl<<jumpReady<<std::endl<<jumping<<std::endl;
			jumping=true;
			jumpHeight=0;
			jumpSpeed=20;
			jumpReady=false;
		std::cout<<std::endl<<jumpReady<<std::endl<<jumping<<std::endl;
=======
		if (co.collU != TOP) {
			bounds.y -= 10;
>>>>>>> 273ca5fe6ded150fcfa3a1628279df435250a21f
		}
		//sprite.Move(0, -dt*speed);
	} else {
		if(jumpSpeed>0)
		{
			jumpSpeed = 0;
		}
	}
	if(jumping==true)
	{
		if ((co.collType != TOP)&&(jumpHeight<maxJumpHeight)) {
			jumpSpeed-=1;
			bounds.y -= jumpSpeed;
			jumpHeight += jumpSpeed;
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
