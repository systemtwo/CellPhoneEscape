#ifndef GS_H
#define GS_H
#include <iostream>
#include <SFML/graphics.hpp>
#include <cmath>
#include "StateManager.h"
#include "PlayerClass.h"
#include "Engine.h"

#define PI 3.14159265

class GameState: public State {
	private: 
		sf::Sprite backgroundSprite;
		sf::Sprite pointerSprite;
		sf::Sprite sat1Sprite;
		sf::Sprite sat2Sprite;
		const sf::Input & Input;
		
		double time;
		Player player;
		//Engine eng;
	public:
		GameState(sf::RenderWindow *);
		void init();
		void draw();
		void update(float dt);
		directions dirs;
};

#endif
