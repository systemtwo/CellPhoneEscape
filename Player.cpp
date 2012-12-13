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

	jumpReady = true;
	jumpHeight = 0;

	
	name = "player";

	
	return;
}

void Player::resolveCollisions(CollisionObj co)
{
	co = eng->detectCollisions(bounds, this);
	float temp = 600; //Arbitrarily large
	int Dir_id = 0;
	if(((co.distD<temp)&&(co.distD!=0))
		&&  (!((co.collD)&&(co.collU))	
		         ||
			((co.collL)&&(co.collR)))) 
	{
			
		temp = co.distD;
		Dir_id = 1;
	}
	if(((co.distU<temp)&&(co.distU!=0))
		&&  (!((co.collD)&&(co.collU))	
		         ||
			((co.collL)&&(co.collR))))
	{
			
		temp = co.distU;
		Dir_id = 2;
	}
	if(((co.distL<temp)&&(co.distL!=0))
		&&  (!((co.collL)&&(co.collR))	
		         ||
			((co.collD)&&(co.collU))))
	{
		temp = co.distL;
		Dir_id = 3;
	}
	if(((co.distR<temp)&&(co.distR!=0))
		&&  (!((co.collL)&&(co.collR))	
		         ||
			((co.collD)&&(co.collU))))
	{
		temp = co.distR;
		Dir_id = 4;
	}
	using namespace std;
	switch (Dir_id) {
	case 1:
		cout<<endl<<"Moved it Up "<<temp<<" units"<<endl;
		bounds.y-=temp;
		jumpSpeed=0;
		jumpReady=true;
		break;
	case 2:
		cout<<endl<<"Moved it down "<<temp<<" units"<<endl
			<<"co.distD = "<<co.distD<<endl
			<<"co.collU = "<<co.collU<<endl;
		if(jumpSpeed>0){
			jumpSpeed=0;
		}
		bounds.y+=temp;
		break;
	case 3:
		cout<<endl<<"Moved it right "<<temp<<" units"<<endl;
		bounds.x+=temp;
		break;
	case 4:
		cout<<endl<<"Moved it left "<<temp<<" units"<<endl;
		bounds.x-=temp;
		break;
	default:;
	}
		
	
	return;
}

void Player::update(float dt) {
	int speed = 200;
	CollisionObj co = eng->detectCollisions(bounds, this);
	
	
	
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
			jumpHeight=0;
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
	jumpHeight += jumpSpeed;
	
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
