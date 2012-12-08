//Engine

#include "Engine.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>

using namespace std;

CollisionObj::CollisionObj(int _ctype, BoundingBox b = BoundingBox()) {
	collType = _ctype;
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
	cout << "FPS" << fps  << "  dt: " << dt << endl;;
	char buffer [1000];
	itoa(fps, buffer, 10);
	if (counter % 10 == 0) {
		text.SetText(buffer);
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



bool compareDrawObjZOrder(DrawObj * i, DrawObj * j) {
	return (i->zorder) < (j->zorder);
}

void Engine::addDrawObj(DrawObj *obj) {
	objList.push_back (obj);
	return;
}

DrawObj * Engine::makeAndAddObj(sf::Sprite * _sprite, int _zorder) {
	//Does addDrawObj, but first wraps it for the user
	DrawObj * tempobj = new DrawObj;
	tempobj->sprite = _sprite;
	tempobj->zorder = _zorder;
	tempobj->destroy = false;
	addDrawObj(tempobj);
	return tempobj;
}

void Engine::drawAll() {
	cout << "Tracking " << objList.size() << endl;
	cleanObjList();
	sortZOrder();
	for (int i = 0; i < objList.size(); i++) {
		typeid(objList[i]->sprite).name();
		AppPointer->Draw(*(objList[i]->sprite));
	}
	return;
}

void Engine::sortZOrder() {
	sort(objList.begin(), objList.end(), compareDrawObjZOrder);
	return;
}

void Engine::cleanObjList() {
	for (int i = 0; i < objList.size(); i++) {
		if (objList[i]->destroy == true) {
			delete objList[i];
			objList.erase(objList.begin() + i);
		}
	}
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
	

	
	cout << "Tracking GenObj: " << genObjList.size() << endl;
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
	for (int i = 0; i < genObjList.size(); i++) {
		if (_origin == genObjList[i]) {
			//Object is being compared with itself
			cout << "Self hit" << endl;
			continue;
		}
		aa = genObjList[i]->getBounds();
		
		if(aa.h == 0 && aa.w == 0) {
			cout << "Passing" << endl;
			continue;
		}
		if (((bb.y+bb.h) > aa.y) && (bb.y < aa.y) && (bb.x < (aa.x+aa.w)) && ((bb.x+bb.w)> (aa.x))) {
			return CollisionObj(BOTTOM, aa);
		} else if (((bb.y) < (aa.y+aa.h)) && ((bb.y+bb.h) > aa.y) && (bb.x < (aa.x+aa.w)) && ((bb.x+bb.w)> (aa.x))) {
			return CollisionObj(TOP, aa);
		} 
	}
	return CollisionObj(NONE);
}
