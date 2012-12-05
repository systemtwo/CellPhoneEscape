#ifndef TS_H
#define TS_H

#include <iostream>
#include <SFML/graphics.hpp>
#include "StateManager.h"
#include "Engine.h"

class TitleState: public State {
	private: 
		sf::Sprite titleSprite;
		sf::Sprite pointerSprite;
		const sf::Input & Input;
		Engine eng;
		DrawObj * tmp;
		DrawObj * mouse;
	public:
		TitleState(const sf::Input &);
		void init();
		void draw();
		void update(float dt);
};

#endif
