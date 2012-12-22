#ifndef ENEMIES_H
#define ENEMIES_H


#include <SFML/graphics.hpp>
#include <iostream>
#include <string>
#include "Engine.h"
#include "ResourceManager.h"
#include "Player.h"

using namespace std;

class FallingBlock : public GenericObj {
	public:
		//FallingBlock(){}
		FallingBlock(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
		BoundingBox bounds;
		
	private:
		void resolveCollisions(CollisionObj co);
		sf::RenderWindow * AppPointer;
		sf::Sprite sprite;
		Player * playerptr;
		Engine * eng;
		float fallSpeed;
		float moveSpeed;
		bool bounce;
		bool secbounce;
};

class SecBot : public GenericObj {
	public:
		SecBot(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
		BoundingBox bounds;
	private:
		void resolveCollisions(CollisionObj co);
		sf::RenderWindow * AppPointer;
		sf::Sprite sprite;
		Engine * eng;
		Player * playptr;
		
		const static int extraDist = 400*400; //Distance at which sbot is a lot more likely to come towards player
		const static int moveBiasL = 4, moveBiasS = 3, swC_init = 600, favor_init = 2;
		int switchChance;
		enum moveDirections {LEFT, RIGHT, UP, DOWN};
		int moveDir;
		
		//int moveH, moveV;
		
		float speed;
		
	
};
class Laser : public GenericObj {
	public:
		Laser(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player, int start_x, int end_x, int top_y, int bot_y);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
	private:
		sf::RenderWindow * AppPointer;
		sf::Sprite topSprite, botSprite;
		Engine * eng;
		Player * playerptr;
		ResourceManager * resourceM;
		
		float length;
		string name;
		float curX, endX, topY, botY, curTopY, curBotY, origY;
};

#endif
