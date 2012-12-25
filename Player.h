#ifndef PC_H
#define PC_H

#include <SFML/graphics.hpp>

#include <cstdlib>

#include "Engine.h"
#include "ResourceManager.h"
using namespace std;



class Player : public GenericObj {
	public:
		Player(sf::RenderWindow * _ap, ResourceManager * _rm, Engine * _eng, int x = 100, int y = 100);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
		float health;
		//int zorder;
		//BoundingBox abilityRange;
	private:
		void resolveCollisions(CollisionObj co);
		sf::RenderWindow * AppPointer;
		const sf::Input & input;
		sf::Sprite sprite;
		Engine * eng;
		bool jumpReady;
		float jumpHeight, jumpSpeed;
		static const int initSpeed = 15;
		static const float ACCELERATION = 0.35;
		static const float safeFallSpeed = 14;
		static const float RANGE = 5;
		BoundingBox abilityRange; 
		sf::Font font;
		sf::String healthdisp;
		
};

#endif
