#ifndef GS_H
#define GS_H
#include <iostream>
#include <SFML/graphics.hpp>
#include <cmath>
#include "StateManager.h"
#include "Player.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "TileManager.h"

#define PI 3.14159265

class GameState: public State {
	private: 
		const sf::Input & Input;

		Engine eng;
		TileManager tm;
		ResourceManager * RMPointer;
	public:
		GameState(sf::RenderWindow *, ResourceManager *);
		void init();
		void draw();
		void update(float dt);
		//directions dirs;
};

#endif
