//Engine

#include "Engine.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <sstream>


using namespace std;

CollisionObj::CollisionObj(BoundingBox b = BoundingBox()) {
	collL = false;
	collR = false;
	collU = false;
	collD = false;
	
	distL = 0;
	distR = 0;
	distU = 0;
	distD = 0;
	
	bounds = b;
	return;
}

BoundingBox::BoundingBox() {
	x = 0;
	y = 0;
	h = 0;
	w = 0;
	
	return;
}

FPSDisplay::FPSDisplay() {
	font.LoadFromFile("snr.ttf");
	text.SetFont(font);
	text.SetSize(50);
	counter = 0;
	
	setZOrder(100);
	return;
}

void FPSDisplay::update(float dt) {
	fps = 1/dt;
	//cout << "FPS" << fps  << "  dt: " << dt << endl;
	/*char buffer [1000];
	itoa(fps, buffer, 10);*/
	
	stringstream ss;
	ss << (int)fps;
	if (counter % 10 == 0) {
		text.SetText(ss.str());
		counter = 1;
	}
	
	counter ++;
	
	return;
}

void FPSDisplay::draw(sf::RenderWindow * _ap) {
	_ap->Draw(text);
	return;
}


///MEMTESTER
void MemTester::draw(sf::RenderWindow * _ap) {
	if (_ap->GetInput().IsKeyDown(sf::Key::Return)) {
		selfDestruct();
	}
	return;
}

void MemTester::update(float dt) {
	return;
}

/////MEMTESTER End


Background::Background(sf::RenderWindow * _ap, ResourceManager * _rm) {
	AppPointer = _ap;
	sprite.SetImage(*_rm->getImage("background"));
	
	//Set bounds
	bounds.x = -50;
	bounds.y = -50;
	bounds.w = sprite.GetSize().x;
	bounds.h = sprite.GetSize().y;

	setZOrder(0);
	name = "background";
	return;
}

void Background::update(float dt) {
	const sf::Input & input = AppPointer->GetInput();
	if (input.IsKeyDown(sf::Key::Left)) {
		bounds.x += 0;
	}
	sprite.SetX(bounds.x);
	sprite.SetY(bounds.y);
	return;
}

void Background::draw(sf::RenderWindow * _ap) {
	AppPointer->Draw(sprite);
	return;
}

GenericObj::GenericObj() {
	destroy = false;
	return;
}

void GenericObj::setZOrder(int _z) {
	zorder = _z;
	return;
}

int GenericObj::getZOrder() {
	return zorder;
}

void GenericObj::selfDestruct() {
	destroy = true;
	return;
}

void GenericObj::draw(sf::RenderWindow * _ap) {
	return;
}

void GenericObj::update(float dt) {
	return;
}

BoundingBox GenericObj::getBounds() {
	return bounds;
}


bool compareGenObjZOrder(GenericObj * i, GenericObj * j) {
	return (i->getZOrder()) < (j->getZOrder());
}





void Engine::setAppPointer(sf::RenderWindow * _ap) {
	AppPointer = _ap;
	return;
}

void Engine::addGenObj(GenericObj * genobj) { 
	genObjList.push_back(genobj);
	//std::cout << genobj->zorder << std::endl;
	return;
	
}

void Engine::drawAllGenObj() {
	for (int i = 0; i < genObjList.size(); i++) {
		genObjList[i]->draw(AppPointer);
	}
	return;
}

void Engine::deleteAllGenObj() {
	std::cout << "Attempting to delete " << genObjList.size() << " objects" << std::endl;
	for (int i = 0; i < genObjList.size(); i++) {
		delete genObjList[i];
		genObjList.erase(genObjList.begin() + i);
	}
}

void Engine::updateAllGenObj(float dt) {
	
	//Debug
	/*
	if (genObjList.size()% 100 == 0) {
		for (int i = 0; i < genObjList.size(); i++) {
			std::cout << genObjList[i]->zorder << " ";
		}
		std::cout << std::endl;
		system("pause");
	}*/
	
	//Clean destroyed items
	for (int i = 0; i < genObjList.size(); i++) {
		if (genObjList[i]->destroy == true) {
			delete genObjList[i];
			genObjList.erase(genObjList.begin() + i);
		}
	}

	stable_sort(genObjList.begin(), genObjList.end(), compareGenObjZOrder); //Sort z orders
	

	
//	cout << "Tracking GenObj: " << genObjList.size() << endl;
	for (int i = 0; i < genObjList.size(); i++) {
		genObjList[i]->update(dt);
	}
	return;
}

CollisionObj Engine::detectCollisions(BoundingBox bb, GenericObj * _origin) {
	//Returns 1-4 for each side(enum-ed)
	
	/*
	cout << "1 (" << bb.x << ", " << bb.y << endl
	     << "2 (" << bb.x+bb.w << ", " << bb.y << endl
		 << "3 (" << bb.x << ", " << bb.y+bb.h << endl
		 << "4 (" << bb.x+bb.w << ", " << bb.y+bb.h << endl;
		 */
	BoundingBox aa; //Temp storage for the items in list
	
	bool colU = false;
	bool colD = false;
	bool colR = false;
	bool colL = false;
	
	int temp = 0;
	
	CollisionObj co = CollisionObj(aa);
	for (int i = 0; i < genObjList.size(); i++) {
		//Reset colision values
		/*
		colU = false;
		colD = false;
		colR = false;
		colL = false;
		*/
		if (_origin == genObjList[i]) {
			//Object is being compared with itself
			//cout << "Self hit" << endl;
			
			continue;
		}
		aa = genObjList[i]->getBounds();
		
		
		if(aa.h == 0 && aa.w == 0) {
			//These objects are set to not have a bounding box
			//cout << "Passing" << endl;
			continue;
		}
		
		if (((bb.x+bb.w) > (aa.x)) && ((bb.x) < (aa.x)) && (bb.y < (aa.y+aa.h)) && ((bb.y+bb.h) > (aa.y))) {
			//cout << "Right" << endl;
			co.collR = true;
			if (((bb.x+bb.w)-aa.x)>co.distR) { //Find out if the overlap dist is bigger
				co.distR = (bb.x+bb.w)-aa.x;
			}
			co.nameR.push_back(genObjList[i]->name);
			if((genObjList[i]->name.compare("tile")))
			//cout<<"Name is "<<genObjList[i]->name<<endl<<endl;
			if(co.nameR.size()>temp) {
				temp=co.nameR.size();
			}
		}
		//cout << "Rd: " << ((bb.x) < (aa.x)) << endl;
		else if ((bb.x < (aa.x+aa.w)) && ((bb.x+bb.w) > (aa.x+aa.w)) && (bb.y < (aa.y+aa.h)) && ((bb.y+bb.h) > (aa.y))) {
			//cout << "LEFT" << ((bb.x+bb.w) > (aa.x+aa.w)) <<  endl;
			co.collL = true;
			if (((aa.x+aa.w)-bb.x)>co.distL) {
				co.distL = (aa.x+aa.w)-bb.x;
			}
			co.nameL.push_back(genObjList[i]->name);
			if((genObjList[i]->name.compare("tile")))
			//cout<<"Name is "<<genObjList[i]->name<<endl<<endl;
			if(co.nameL.size()>temp) {
				temp=co.nameL.size();
			}
		}
		
		if (((bb.y+bb.h) > aa.y) && (bb.y < aa.y) && (bb.x < (aa.x+aa.w)) && ((bb.x+bb.w)> (aa.x))) {
			//return CollisionObj(BOTTOM, aa);
			//cout << "BOTTOM" << endl;
			co.collD = true;
			if (((bb.y+bb.h)-aa.y) > co.distD) {
				co.distD = (bb.y+bb.h)-aa.y;
			}
			co.nameD.push_back(genObjList[i]->name);
			if((genObjList[i]->name.compare("tile")))
			//cout<<"Name is "<<genObjList[i]->name<<endl<<endl;
			if(co.nameD.size()>temp) {
				temp=co.nameD.size();
			}
		} else if (((bb.y) < (aa.y+aa.h)) && ((bb.y+bb.h) > (aa.y+aa.h)) && (bb.x < (aa.x+aa.w)) && ((bb.x+bb.w)> (aa.x))) {
			//This else if may cause some later problems
			//return CollisionObj(TOP, aa);
			//cout << "UP" << endl;
			co.collU = true;
			if (((aa.y+aa.h)-bb.y)> co.distU) {
				co.distU = (aa.y+aa.h)-bb.y;
			}
			co.nameU.push_back(genObjList[i]->name);
			if((genObjList[i]->name.compare("tile")))
			//cout<<"Name is "<<genObjList[i]->name<<endl<<endl;
			if(co.nameU.size()>temp) {
				temp=co.nameU.size();
			}
		} else {
			//Return CollisionObj with side set and top/bottom set to none
		}
		
		
	}
	co.maxNameVectorSize = temp; //Sets it to the size of the name vector with the largest size
	
	return co;
	//return CollisionObj(NONE);
}
