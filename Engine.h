#ifndef Engine_H
#define Engine_H

#include <vector>
#include <SFML/graphics.hpp>
#include <string>

enum direction {NONE, TOP, BOTTOM, LEFT, RIGHT};



class BoundingContainer {
	public: 
		float x, y;
};

class BoundingBox: public BoundingContainer {
	public: 
		BoundingBox();
		float w, h;
};

class BoundingCircle: public BoundingContainer {
	public:
		float r;
};

class CollisionObj {
	public:
		CollisionObj(int ctype, BoundingBox b);
		BoundingBox bounds;
		int collType; //Collision type as determined by enum
};

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
		void selfDestruct();
		BoundingBox getBounds();
		
		std::string name;
		bool destroy;
		bool subscribeInput; //If the object want inputs called
		
	private:
		int zorder;
		
	protected:
		BoundingBox bounds;
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
		CollisionObj detectCollisions(BoundingBox bb, GenericObj * _origin);
		
	private:
		std::vector<DrawObj*> objList;
		std::vector<GenericObj *> genObjList;
		void sortZOrder();
		void cleanObjList();
		sf::RenderWindow * AppPointer;		
};

#endif
