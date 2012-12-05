#include <iostream>
#include <SFML/graphics.hpp>
#include "StateManager.h"

class LoaderState: public State {
	private: 
		sf::Sprite loaderSprite;
		const sf::Input & Input;
	public:
		LoaderState(const sf::Input &);
		void init();
		void draw();
		void update();
};
