#ifndef ENEMIES_H
#define ENEMIES_H


#include <SFML/graphics.hpp>

#include "Engine.h"
#include "ResourceManager.h"
#include <iostream>
using namespace std;

class FallingBlock : public GenericObj {
	public:
		FallingBlock(){}
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

#endif
