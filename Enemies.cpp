

#include "Enemies.h"
#include "LevelManager.h"
#include <cstdlib>
#include "Vector2.hpp"
const int HEIGHT = 30, WIDTH = 25;

FallingBlock::FallingBlock(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player) {
	playerptr = _player;
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
	bounce = false;
	secbounce = false;
	
	name = "fallBlock";

	
	return;
}
void FallingBlock::resolveCollisions(CollisionObj co){
	if((co.collD)) { 
		//Iterate thru objs it colides with on bottom
		for (int i= 0; i < co.nameD.size(); i++) {
			if((co.nameD[i]=="player")) {
				selfDestruct();    //Add extra effects later, in a private member function.
			} else if ((co.nameD[i]=="tile")) {
				if((fallSpeed>0) && !(co.collU) && bounce == false){
					//First bounce
					bounds.y-=fallSpeed;
					fallSpeed *= -.5;
					moveSpeed *= 0.8;
					bounce = true;
					secbounce = false;
				} else if ((fallSpeed>0) && !(co.collU) && bounce == true) {
					//second bounce
					secbounce = true;
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
	if (!co.collD && secbounce == true) {
		bounce = false;
		secbounce = false;
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
	if(bounds.y>HEIGHT*TILE_SIZE) {
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
	bounds.x = rand()%100 + 400;
	bounds.y = rand()%10 + 300;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;
	
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	
	setZOrder(10);
	
	//moveV = 15;
	//moveH = 15;
	moveDir = rand()%4;
	switchChance = 10;
	
	
	name = "secbot";
	
	return;
}

void SecBot::resolveCollisions(CollisionObj co){
	//"Ghost" enemy, allowed to go thru tiles/walls
	int temp = rand()%2;
	if((co.collD)) { 
		//Iterate thru objs it colides with on bottom
		if(!( ((co.distD > co.distR) && (co.collR)) || ((co.distD > co.distL) && (co.collL)) || ((co.distD > co.distU) && (co.collU)) )) {
			bounds.y -= co.distD;
			if(temp) {
				moveDir = LEFT;
			} else {
				moveDir = RIGHT;
			}
		}
		for (int i= 0; i < co.nameD.size(); i++) {
			if((co.nameD[i]=="player")) {
				selfDestruct();    //Add extra effects later, in a private member function.
			} 
				
		}
	}
	if (co.collU) {
		if(!( ((co.distU > co.distD) && (co.collD)) || ((co.distU > co.distL) && (co.collL)) || ((co.distU > co.distR) && (co.collR)) )) {
			bounds.y += co.distU;
			if(temp) {
				moveDir = LEFT;
			} else {
				moveDir = RIGHT;
			}
		}
		for(int i= 0; i < co.nameU.size(); i++) {
			if(co.nameU[i]=="player") {
				selfDestruct();
				//cout<<"Destroy Up";
				
			} 
		}
	}
	
	if ((co.collL)) {
		if(!( ((co.distL > co.distD) && (co.collD)) || ((co.distL > co.distR) && (co.collR)) || ((co.distL > co.distU) && (co.collU)) )) {
			bounds.x += co.distL;
			if(temp) {
				moveDir = UP;
			} else {
				moveDir = DOWN;
			}
		}
		for (int i= 0; i < co.nameL.size(); i++) {
			if(co.nameL[i]=="player"){
				
				selfDestruct();
			}
		}
	}
	
	
			
	if (co.collR) {
		if(!( ((co.distR > co.distD) && (co.collD)) || ((co.distR > co.distL) && (co.collL)) || ((co.distR > co.distU) && (co.collU)) )) {
			bounds.x -= co.distR;
			if(temp) {
				moveDir = UP;
			} else {
				moveDir = DOWN;
			}
		}
		for (int i= 0; i < co.nameR.size(); i++) {
			if(co.nameR[i]=="player") {
				selfDestruct();
				//cout<<"Destroy Right";
			}
		}
	}
}

void SecBot::update(float dt) {
	//int favorH = 0;
	//int favorV = 0;
	
	int xDif = playptr->getBounds().x - bounds.x; //Positive if player is on right of sec bot
	int yDif = playptr->getBounds().y - bounds.y; //Positive if player is below sec bot
	int totalDif = xDif*xDif + yDif*yDif; //Don't bother sqrt, wasted time
	int favor = favor_init;
	
	
	if((yDif>=0) && (xDif>=0)) {
		if((moveDir == LEFT) || (moveDir == UP)) {
			if(totalDif > extraDist) {
				favor = moveBiasL;
			} else {
				favor = moveBiasS;
			}
		}
	} else if((yDif>=0) && (xDif<0)) {
		if((moveDir == RIGHT) || (moveDir == UP)) {
			if(totalDif > extraDist) {
				favor = moveBiasL;
			} else {
				favor = moveBiasS;
			}
		}
	} else if((yDif<0) && (xDif>=0)) {
		if((moveDir == LEFT) || (moveDir == DOWN)) {
			if(totalDif > extraDist) {
				favor = moveBiasL;
			} else {
				favor = moveBiasS;
			}
		}
	} else if((yDif<0) && (xDif<0)) {
		if((moveDir == RIGHT) || (moveDir == DOWN)) {
			if(totalDif > extraDist) {
				favor = moveBiasL;
			} else {
				favor = moveBiasS;
			}
		}
	}
	
	if(rand()%abs(switchChance) <= favor) {//Smaller switchChance gets, more likely to switch direction
		moveDir += rand()%3 + 1;
		if(moveDir > 3) {
			moveDir -= 4;
		}
		switchChance = swC_init;
	}
	if(switchChance>1) {
		switchChance--;
	}
	switch(moveDir) {
		case LEFT:
			bounds.x -= speed * dt;
			break;
		case RIGHT:
			bounds.x += speed *dt;
			break;
		case UP:
			bounds.y -= speed *dt;
			break;
		case DOWN:
			bounds.y += speed * dt;
			break;
		default:
			cout<<"ERROR in moveDir"<<endl;
			break;
	}
	
	/*if (playptr->getBounds().x > bounds.x) {
		if (playptr->getBounds().x > bounds.x + extraDist) {
			if(moveH > 0) {
				favorH = 0;
			} else {
				favorH = moveBiasL;
			}
		} else {
			if(moveH > 0) {
				favorH = 0;
			} else {
				favorH = moveBiasS;
			}
		}
	} else if (playptr->getBounds().x < bounds.x) {
		if (playptr->getBounds().x < bounds.x - extraDist) {
			if(moveH < 0) {
				favorH = 0;
			} else {
				favorH = moveBiasL;
			}
		} else {
			if(moveH < 0) {
				favorH = 0;
			} else {
				favorH = moveBiasS;
			}
		}
	}
	if (playptr->getBounds().y > bounds.y) {
		if (playptr->getBounds().y > bounds.y + extraDist) {
			if(moveV > 0) {
				favorV = 0;
			} else {
				favorV = moveBiasL;
			}
		} else {
			if(moveV > 0) {
				favorV = 0;
			} else {
				favorV = moveBiasS;
			}
		}
	} else if (playptr->getBounds().y < bounds.y) {
		if (playptr->getBounds().y < bounds.y - extraDist) {
			if(moveV < 0) {
				favorV = 0;
			} else {
				favorV = moveBiasL;
			}
		} else {
			if(moveV < 0) {
				favorV = 0;
			} else {
				favorV = moveBiasS;
			}
		}
	}
	if(rand()%abs(moveH) <= favorH) {//Smaller moveH gets, more likely to switch direction
		moveH *= -1;
		moveH = (rand()%moveDist + minMove) * moveH / abs(moveH);
	}
	if(rand()%abs(moveV) <= favorV) {
		moveV *= -1;
		moveV = (rand()%moveDist + minMove) * moveV / abs(moveV);
	}
	
	if(moveH >= 0) {
		if(moveH > 1) {
			moveH--;
		}
		bounds.x += speed*dt;
	} else if(moveH < 0) {
		if(moveH < -1) {
			moveH++;
		}
		bounds.x -=speed*dt;
	}
	
	if(moveV >= 0) {
		if(moveV > 1) {
			moveV--;
		}
		bounds.y += speed*dt;
	} else if(moveV < 0) {
		if(moveV < -1) {
			moveV++;
		}
		bounds.y -=speed*dt;
	}*/
	
	
	
	
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





Laser::Laser(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player, int start_x, int end_x, int top_y, int bot_y) {
	AppPointer = _ap;
	resourceM = _rm;
	topSprite.SetImage(*_rm -> getImage("laserV"));
	botSprite.SetImage(*_rm -> getImage("laserV"));
	botSprite.FlipY(true);
	botSprite.SetY(bot_y);
	topSprite.SetY(top_y);
	topSprite.SetScaleX(0.2);
	botSprite.SetScaleX(0.2);
	
	
	eng = _eng;
	playerptr = _player;
	
	curX = start_x;
	endX = end_x;
	topY = top_y;
	botY = bot_y;
	origY = botSprite.GetSize().y;
}

void Laser::update(float dt) {
	bool hitPlayer = false;
	curTopY = topY;
	curBotY = botY - 1;
	while((eng -> detectPointCollision(curX, curTopY, name) == -1) && (curTopY < botY)) {
		curTopY ++;
	}
	if(name == "player") {
		cout << "Hit player"<<endl;
		hitPlayer = true;
		eng->addGenObj(new SecBot(AppPointer, resourceM, eng, playerptr));
	}
	
	topSprite.SetScaleY((curTopY - topY)/origY);
	topSprite.SetX(curX);
	
	while((eng -> detectPointCollision(curX, curBotY, name) == -1)&&(curBotY > curTopY)) {
		curBotY --;
	}
	if(name == "player") {
		cout << "Hit player"<<endl;
		if(hitPlayer == false) {
			eng->addGenObj(new SecBot(AppPointer, resourceM, eng, playerptr));
		}
	}
	
	botSprite.SetScaleY((botY - curBotY)/origY);
	botSprite.SetX(curX);
	botSprite.SetY(curBotY);
	
	curX++;
	if(curX >= endX) {
		selfDestruct();
	}
	
}

void Laser::draw(sf::RenderWindow * _ap) {
	_ap->Draw(topSprite);
	_ap->Draw(botSprite);
	return;
}
