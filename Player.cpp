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

void Player::resolveCollisions(CollisionObj co)
{
	co = eng->detectCollisions(bounds, this);
	if (co.collD == true ) {
		jumpReady=true;
		jumping = false;
	} else if(jumping==false){
		jumping=true;
		jumpSpeed=0;
	}
	/*if((co.collD == true)&&(co.collU == true)){
		bounds.x+=co.distL;
		bounds.x-=co.distR;
	} else if((co.collL == true)&&(co.collR == true)){
		bounds.y-=co.distD;
		bounds.y+=co.distU;
	} else {
		bounds.y-=co.distD;
		bounds.y+=co.distU;
		bounds.x-=co.distL;
		bounds.x+=co.distR;
	}*/
	if(co.collD==true) {
		bounds.y-=co.distD;
		///bounds.y+=co.distU;
	} else {
		bounds.x+=co.distL;
		bounds.x-=co.distR;
	}	
	
	return;
}

void Player::update(float dt) {
	int speed = 100;
	CollisionObj co = eng->detectCollisions(bounds, this);
	resolveCollisions(co);
	
	std::cout << co.collD;
	
	/*
	std::cout << "COLLIDING WITH: " << std::endl;
	for (int i = 0; i < co.nameD.size(); i++)  {
		std::cout << "-" << co.nameD[i] << std::endl;
	}*/
	
	std::cout << co.distD;
	
	
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
			jumping=true;
			jumpHeight=0;
			jumpSpeed=20;
			jumpReady=false;
		}
	} else {
		if(jumpSpeed>0)
		{
			jumpSpeed = 0;
		}
	}
	if(jumping==true){
		if ((co.collU != true)&&(jumpHeight<maxJumpHeight)) {
			jumpSpeed-=1;
			bounds.y -= jumpSpeed;
			jumpHeight += jumpSpeed;
		}
		if(co.collU==true){
			jumpSpeed=0;
		}
	}
	
	
	if (input.IsKeyDown(sf::Key::Down)) {
		bounds.y += dt*speed;
		//sprite.Move(0, dt*speed);
	}
	
	resolveCollisions(co);
	
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	
	
	
	return;
}

void Player::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}
