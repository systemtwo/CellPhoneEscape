//Engine

#include "Engine.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>

using namespace std;

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
