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
		int getZOrder();
		virtual void draw(sf::RenderWindow * _AP);
		virtual void update(float dt);
		virtual void onMousemove(int x, int y);
		virtual void onKeypress(char);
		void selfDestruct();
		
		
		bool destroy;
		bool subscribeInput; //If the object want inputs called
	private:
		int zorder;
};

class FPSDisplay : public GenericObj {
	public:
		FPSDisplay();
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
	private:
		int fps;
		sf::Font font;
		sf::String text;
		int counter;
};

class MemTester : public GenericObj {
	public:
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		const static int zorder = 1;
		char a[10000000];
};

class BoundingContainer {
	public: 
		float x, y;
};

class BoundingBox: public BoundingContainer {
	public: 
		float w, h;
};

class BoundingCircle: public BoundingContainer {
	public:
		float r;
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
