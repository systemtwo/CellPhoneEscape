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
#include "AudioManager.h"

#define PI 3.14159265

class GameState: public State {
	private: 
		const sf::Input & Input;

		Engine eng;
		LevelManager tm;
		ResourceManager * RMPointer;
		sf::View view;
		Player * playerptr;
		bool laser;
		
		AudioManager AM;
		sf::Sound exp;
	public:
		GameState(sf::RenderWindow *, ResourceManager *);
		void init();
		void draw();
		void update(float dt);
		void onSwitch();
		void onSwitchOut();
		//directions dirs;
};

#endif
