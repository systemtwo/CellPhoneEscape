

#include "Enemies.h"
#include <cstdlib>


FallingBlock::FallingBlock(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("binary"));

	setZOrder(10);
	
	eng = _eng;
	//Set bounds
	bounds.x = rand()%1000;
	bounds.y = rand()%10;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;

	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);

	fallSpeed = 25;
	
	name = "fallBlock";

	
	return;
}
void FallingBlock::resolveCollisions(CollisionObj co){
	//co = eng->detectCollisions(bounds, this);
	if((co.collD)||(co.collU)||(co.collL)||(co.collR)) {
		for(int i = 0; i < co.maxNameVectorSize; i++) {
			int i=0;
			if(co.nameL.size()>i)
			if((!(co.nameL[0].compare("player")))   ){
				cout<<"Destroy Left";
				selfDestruct();
			}
			if(co.nameU.size()>i)
			if((co.nameU[i]=="player")&&(i<co.nameU.size())) {
				selfDestruct();
				cout<<"Destroy Up";
			}
			if(co.nameR.size()>i)
			if((co.nameR[i]=="player")&&(i<co.nameR.size())) {
				selfDestruct();
				cout<<"Destroy Right";
			}
			if(co.nameD.size()>i)
			if((co.nameD[i]=="player")&&(i<co.nameD.size())) {
				cout<<"Destroy Down";
				selfDestruct();    //Add extra effects later, in a private member function.
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
	
	resolveCollisions(co);
	
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	
	return;
}

void FallingBlock::draw(sf::RenderWindow * _ap) {
	_ap->Draw(sprite);
	return;
}
