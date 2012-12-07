#ifndef PC_H
#define PC_H
#include <iostream>
#include <SFML/graphics.hpp>
#include <cmath>
#include "Engine.h"
#include "ResourceManager.h"

enum directions {up, down, left, right};


class Player : public GenericObj {
	public:
		Player(sf::RenderWindow * _ap, ResourceManager * _rm);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
		
		const static int zorder = 10;
	private:
		sf::RenderWindow * AppPointer;
		const sf::Input & input;
		sf::Sprite sprite;
};

#endif
