#include <iostream>
#include <SFML/graphics.hpp>
#include <cmath>
#include "StateManager.h"
#include "PlayerClass.h"

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
	public:
		GameState(const sf::Input &);
		void init();
		void draw();
		void update(float dt);
		directions dirs;
};
