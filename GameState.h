#ifndef GS_H
#define GS_H
#include <iostream>
#include <SFML/graphics.hpp>
#include <cmath>
#include "StateManager.h"
#include "Player.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "LevelManager.h"

#define PI 3.14159265

class GameState: public State {
	private: 
		const sf::Input & Input;

		Engine eng;
		LevelManager tm;
		ResourceManager * RMPointer;
		sf::View view;
		Player * playerptr;
	public:
		GameState(sf::RenderWindow *, ResourceManager *);
		void init();
		void draw();
		void update(float dt);
		void onSwitch();
		//directions dirs;
};

#endif
