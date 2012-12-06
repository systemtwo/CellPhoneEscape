#ifndef Engine_H
#define Engine_H

#include <vector>
#include <SFML/graphics.hpp>


struct DrawObj {
	sf::Sprite * sprite;
	int zorder;
	bool destroy; //Set to true for Engine to destroy
	//string name;
};

class GenericObj {
	public:
		GenericObj();
		void setZOrder(int _z);
		virtual void draw(sf::RenderWindow * _AP);
		virtual void update(float dt);
		void selfDestruct();
		
		int zorder;
		bool destroy;
	private:
		
};

bool compareDrawObjZOrder(DrawObj * i, DrawObj * j);
bool compareGenObjZOrder(GenericObj * i, GenericObj * j);

class Engine {
	public:
		void addDrawObj(DrawObj *obj);
		void drawAll();
		void setAppPointer (sf::RenderWindow * _ap);
		DrawObj * makeAndAddObj(sf::Sprite * _sprite, int _zorder);
		
		void addGenObj(GenericObj * genobj);
		void drawAllGenObj();
		void updateAllGenObj(float dt);
		
	private:
		std::vector<DrawObj*> objList;
		std::vector<GenericObj *> genObjList;
		void sortZOrder();
		void cleanObjList();
		sf::RenderWindow * AppPointer;		
};

#endif
