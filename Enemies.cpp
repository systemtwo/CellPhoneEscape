

#include "Enemies.h"
#include <cstdlib>


FallingBlock::FallingBlock(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("enemy"));

	setZOrder(10);
	
	eng = _eng;
	//Set bounds
	bounds.x = 100; //rand()%1000;
	bounds.y = rand()%10;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;

	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);

	fallSpeed = 2;
	moveSpeed = rand()%10-5;
	
	name = "fallBlock";

	
	return;
}
void FallingBlock::resolveCollisions(CollisionObj co){
	if((co.collD)) { 
		//Iterate thru objs it colides with on bottom
		for (int i= 0; i < co.nameD.size(); i++) {
			cout<<"fallSpeed = " << fallSpeed;
			if((co.nameD[i]=="player")) {
				selfDestruct();    //Add extra effects later, in a private member function.
			} else if ((co.nameD[i]=="tile")) {
				if((fallSpeed>0) && !(co.collU)){
					bounds.y-=fallSpeed;
					fallSpeed *= -.5;
					moveSpeed *= 0.8;
				}
			}
				
		}
	} else if (co.collU) {
		for(int i= 0; i < co.nameU.size(); i++) {
			if(co.nameU[i]=="player") {
				selfDestruct();
				//cout<<"Destroy Up";
				
			} else if ((co.nameU[i]=="tile")) {
				if(fallSpeed<0) {
					bounds.y-=fallSpeed;
					fallSpeed *= -.5;
					moveSpeed *= 0.8;
				}
			}
		}
	}
	
	if ((co.collL)) {
		for (int i= 0; i < co.nameL.size(); i++) {
			if(co.nameL[i]=="player"){
				cout<<"Destroy Left";
				selfDestruct();
			}
		}
	}
	
	
			
	if (co.collR) {
		for (int i= 0; i < co.nameR.size(); i++) {
			if((co.nameR[i]=="player")&&(i<co.nameR.size())) {
				selfDestruct();
				//cout<<"Destroy Right";
			}
		}
	}
}

void FallingBlock::update(float dt) {
	CollisionObj co = eng->detectCollisions(bounds, this);
	
	
	bounds.y += fallSpeed;
	fallSpeed++;
	if(bounds.y>500) {
		selfDestruct();
	}
	bounds.x += moveSpeed;
	
	resolveCollisions(co);
	
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	
	return;
}

void FallingBlock::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}


//////////////////////
//Begin SecBot Code //
//////////////////////

SecBot::SecBot(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player) {
	playptr = _player;
	AppPointer = _ap;
	eng = _eng;
	//RMPointer = _rm;
	speed = 50;
	
	sprite.SetImage(*_rm->getImage("arrgav"));
	//Set bounds
	bounds.x = 100; //rand()%1000;
	bounds.y = rand()%10;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;
	
	setZOrder(10);
	
	name = "secbot";
	
	return;
}

void SecBot::resolveCollisions(CollisionObj co){
	//"Ghost" enemy, allowed to go thru tiles/walls
	if((co.collD)) { 
		//Iterate thru objs it colides with on bottom
		for (int i= 0; i < co.nameD.size(); i++) {
			if((co.nameD[i]=="player")) {
				selfDestruct();    //Add extra effects later, in a private member function.
			} 
				
		}
	} else if (co.collU) {
		for(int i= 0; i < co.nameU.size(); i++) {
			if(co.nameU[i]=="player") {
				selfDestruct();
				//cout<<"Destroy Up";
				
			} 
		}
	}
	
	if ((co.collL)) {
		for (int i= 0; i < co.nameL.size(); i++) {
			if(co.nameL[i]=="player"){
				
				selfDestruct();
			}
		}
	}
	
	
			
	if (co.collR) {
		for (int i= 0; i < co.nameR.size(); i++) {
			if(co.nameR[i]=="player") {
				selfDestruct();
				//cout<<"Destroy Right";
			}
		}
	}
}

void SecBot::update(float dt) {
	if (playptr->getBounds().x > bounds.x) {
		bounds.x += speed * dt;
	} else if (playptr->getBounds().x < bounds.x) {
		bounds.x -= speed * dt;
	} 
	
	if (playptr->getBounds().y > bounds.y) {
		bounds.y += speed * dt;
	} else if (playptr->getBounds().y < bounds.y)  {
		bounds.y -= speed * dt;
	}
	CollisionObj co = eng->detectCollisions(bounds, this);
	resolveCollisions(co);
	
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	return;
}

void SecBot::draw(sf::RenderWindow * _ap) {
	AppPointer->Draw(sprite);
	return;
}
