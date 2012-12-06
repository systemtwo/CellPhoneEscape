//Engine

#include "Engine.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>

using namespace std;

GenericObj::GenericObj() {
	destroy = false;
	return;
}

void GenericObj::setZOrder(int _z) {
	zorder = _z;
	return;
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

void GenericObj::onMousemove(int x, int y) {
	return;
}

void GenericObj::onKeypress(char e) {
	return;
}

bool compareGenObjZOrder(GenericObj * i, GenericObj * j) {
	return (i->zorder) < (j->zorder);
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
	return;
	
}

void Engine::drawAllGenObj() {
	for (int i = 0; i < genObjList.size(); i++) {
		genObjList[i]->draw(AppPointer);
	}
	return;
}

void Engine::updateAllGenObj(float dt) {
	
	//Clean destroyed items
	for (int i = 0; i < genObjList.size(); i++) {
		if (genObjList[i]->destroy == true) {
			delete genObjList[i];
			genObjList.erase(genObjList.begin() + i);
		}
	}

	sort(genObjList.begin(), genObjList.end(), compareGenObjZOrder); //Sort z orders
	

	
	cout << "Tracking GenObj: " << genObjList.size() << endl;
	for (int i = 0; i < genObjList.size(); i++) {
		genObjList[i]->update(dt);
	}
	return;
}
