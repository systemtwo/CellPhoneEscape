#ifndef Engine_H
#define Engine_h

#include <vector>
#include <SFML/graphics.hpp>


struct DrawObj {
	sf::Sprite * sprite;
	int zorder;
	bool destroy; //Set to true for Engine to destroy
	//string name;
};

bool compareDrawObjZOrder(DrawObj * i, DrawObj * j);

class Engine {
	public:
		void addDrawObj(DrawObj *obj);
		void drawAll();
		void setAppPointer (sf::RenderWindow * _ap);
		DrawObj * makeAndAddObj(sf::Sprite * _sprite, int _zorder);
		
	private:
		std::vector<DrawObj*> objList;
		void sortZOrder();
		void cleanObjList();
		sf::RenderWindow * AppPointer;		
};

#endif
