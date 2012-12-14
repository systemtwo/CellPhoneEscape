

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
	moveSpeed = 0;
	
	name = "fallBlock";

	
	return;
}
void FallingBlock::resolveCollisions(CollisionObj co){
	if((co.collD)) { 
		//Iterate thru objs it colides with on bottom
		for (int i= 0; i < co.nameD.size(); i++) {
			if((co.nameD[i]=="player")) {
				//cout<<"Destroy Down";
				selfDestruct();    //Add extra effects later, in a private member function.
			} else if ((co.nameD[i]=="tile")) {
				fallSpeed = 0;
				moveSpeed = -1;
			}
				
		}
	} else {
		//When it is not hitting things
		fallSpeed = 2;
		moveSpeed = 0;
	}
	
	if ((co.collL)) {
		for (int i= 0; i < co.nameL.size(); i++) {
			if(co.nameL[i]=="player"){
				//cout<<"Destroy Left";
				selfDestruct();
			}
		}
	}
	
	if (co.collU) {
		for(int i= 0; i < co.nameU.size(); i++) {
			if((co.nameU[i]=="player")&&(i<co.nameU.size())) {
				selfDestruct();
				//cout<<"Destroy Up";
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
