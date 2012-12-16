#ifndef ENEMIES_H
#define ENEMIES_H


#include <SFML/graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "ResourceManager.h"
#include "Player.h"

using namespace std;

class FallingBlock : public GenericObj {
	public:
		//FallingBlock(){}
		FallingBlock(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
		BoundingBox bounds;
		
	private:
		void resolveCollisions(CollisionObj co);
		sf::RenderWindow * AppPointer;
		sf::Sprite sprite;
		Engine * eng;
		float fallSpeed;
		float moveSpeed;
};

class SecBot : public GenericObj {
	public:
		SecBot(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
	private:
		void resolveCollisions(CollisionObj co);
		sf::RenderWindow * AppPointer;
		sf::Sprite sprite;
		Engine * eng;
		Player * playptr;
		
		float speed;
		
	
};

class Laser : public GenericObj {
	public:
		Laser(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, Player * _player, int start_x, int end_x, int top_y, int bot_y);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
	private:
		void resolveCollisions(CollisionObj co);
		sf::RenderWindow * AppPointer;
		sf::Sprite sprite;
		Engine * eng;
		Player * playptr;
		
		float length;
};

#endif
