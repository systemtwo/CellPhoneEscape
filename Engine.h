#ifndef Engine_H
#define Engine_H

#include <vector>
#include <SFML/graphics.hpp>
#include <string>
#include "ResourceManager.h"

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
		
		enum typeEnum {VIRUS, EPUB, TXT, MP3, JPEG, EXE, ZIP, MOV, DAT, BIN, LOG, BAT, SMS, WAV}; //WAV is for voicemail, SMS for txt msg
		typeEnum type;
		
	private:
		int zorder;
		
	protected:
		BoundingBox bounds;
};

class CollisionObj {
	public:
		CollisionObj(BoundingBox b);
		BoundingBox bounds;
		//int collType; //Collision type as determined by enum
		bool collL; //Collision for sides
		bool collR;
		bool collU;
		bool collD;
		

		//Distance of overlap (Should replace bool versions)
		float distL;
		float distR;
		float distU;
		float distD;
		
		//Names of things collided with (Organized by sizes)
		std::vector<std::string> nameL;
		std::vector<std::string> nameR;
		std::vector<std::string> nameD;
		std::vector<std::string> nameU;
		
		std::vector<GenericObj*> objPtrL;
		std::vector<GenericObj*> objPtrR;
		std::vector<GenericObj*> objPtrD;
		std::vector<GenericObj*> objPtrU;
		
		int maxNameVectorSize;
};

class FPSDisplay : public GenericObj {
	public:
		FPSDisplay();
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
	private:
		float fps;
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

class Background : public GenericObj {
	public:
		Background(sf::RenderWindow * _ap, ResourceManager * _rm);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
	private:
		sf::Sprite sprite;
		sf::RenderWindow * AppPointer;
		
};



bool compareGenObjZOrder(GenericObj * i, GenericObj * j);

class Engine {
	public:
		
		void setAppPointer (sf::RenderWindow * _ap);
		
		
		void addGenObj(GenericObj * genobj);
		void drawAllGenObj();
		void updateAllGenObj(float dt);
		void deleteAllGenObj();
		CollisionObj detectCollisions(BoundingBox bb, GenericObj * _origin);
		int detectPointCollision(float _x, float _y, std::string& _name); //Returns index of obj at point (_x,_y). If no object, returns -1
		
	private:
		std::vector<DrawObj*> objList;
		std::vector<GenericObj *> genObjList;
		sf::RenderWindow * AppPointer;		
};

#endif
