#include "Player.h"
#include <cmath>
#include <iostream>
#include "Enemies.h"


Player::Player(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, int x, int y) : input(_ap->GetInput()) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("player"));

	setZOrder(10);
	
	eng = _eng;
	//Set bounds
	bounds.x = x;
	bounds.y = y;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;

	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);

	jumpReady = true;

	
	name = "player";
	health = 100;
	
	return;
}


void Player::resolveCollisions(CollisionObj co)
{
	co = eng->detectCollisions(bounds, this);
	float temp = 600; //Arbitrarily large
	int Dir_id = 0;
	enum overlapDir {DOWN = 1, UP, LEFT, RIGHT};
	
	//Finds the smallest overlap distance, and pushes the player back that amount
	if(((co.distD<temp)&&(co.distD!=0)) //If it is overlapping on the bottom, and the overlap distance is the smallest so far
		&&  (!((co.collD)&&(co.collU))	//If player is touching above and below, assume it's "in" a wall Do not push up or down
		         ||
			((co.collL)&&(co.collR)))) //If it is touching left, right, top, and bottom, then player is in a corner. Could be pushed
	{
			
		temp = co.distD;
		Dir_id = DOWN;
	}
	if(((co.distU<temp)&&(co.distU!=0))
		&&  (!((co.collD)&&(co.collU))	
		         ||
			((co.collL)&&(co.collR))))
	{
			
		temp = co.distU;
		Dir_id = UP;
	}
	if(((co.distL<temp)&&(co.distL!=0))
		&&  (!((co.collL)&&(co.collR))	
		         ||
			((co.collD)&&(co.collU))))
	{
		temp = co.distL;
		Dir_id = LEFT;
	}
	if(((co.distR<temp)&&(co.distR!=0))
		&&  (!((co.collL)&&(co.collR))	
		         ||
			((co.collD)&&(co.collU))))
	{
		temp = co.distR;
		Dir_id = RIGHT;
	}
	switch (Dir_id) {
	case DOWN:
		//cout<<endl<<"Moved it Up "<<temp<<" units"<<endl;
		bounds.y-=temp;
		if(abs(jumpSpeed) - safeFallSpeed > 0) {
			health -= abs(jumpSpeed) - safeFallSpeed;
			cout << health << "hp and jumpSpeed: " << jumpSpeed << endl;;
		}
		
		jumpSpeed=0;
		jumpReady=true;
		break;
	case UP:
		//cout<<endl<<"Moved it down "<<temp<<" units"<<endl;
		if(jumpSpeed>0){
			jumpSpeed=0;
		}
		bounds.y+=temp;
		break;
	case LEFT:
		//cout<<endl<<"Moved it right "<<temp<<" units"<<endl;
		bounds.x+=temp;
		break;
	case RIGHT:
		//cout<<endl<<"Moved it left "<<temp<<" units"<<endl;
		bounds.x-=temp;
		break;
	default:;
	}
		
	
	return;
}

void Player::update(float dt) {
	int speed = 200;
	CollisionObj co = eng->detectCollisions(bounds, this);
	
	
	/*
	std::cout << "COLLIDING WITH: " << std::endl;
	for (int i = 0; i < co.nameD.size(); i++)  {
		std::cout << "-" << co.nameD[i] << std::endl;
	}*/
	
	
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
			jumpSpeed=initSpeed;
			jumpReady=false;
		}
	} else {
		if(jumpSpeed>0)
		{
			jumpSpeed = 0;
		}
	}
	
	if (input.IsKeyDown(sf::Key::Down)) {
		jumpSpeed-=ACCELERATION;
		//sprite.Move(0, dt*speed);
	}
	
	//Code for falling, and acceleration.
	jumpSpeed -= ACCELERATION;
	bounds.y -= jumpSpeed;
	
	for(int i = 0; i<4 ; i++) {
		resolveCollisions(co);
	}
	
	sprite.SetX(bounds.x+1);
	sprite.SetY(bounds.y+1);
	
	
	
	return;
}

void Player::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}
