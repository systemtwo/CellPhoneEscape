#ifndef GOS_H
#define GOS_H

#include "StateManager.h"
#include "Engine.h"
#include <SFML/graphics.hpp>


class GameOverBackdrop : public GenericObj {
	public:
		GameOverBackdrop(sf::RenderWindow * _ap, ResourceManager * _rm);
		void update(float dt);
		void draw(sf::RenderWindow * _ap);
	private:
		sf::Sprite sprite;
		sf::RenderWindow * AppPointer;
};

class GameOverState : public State {
	private: 
		const sf::Input & Input;
		sf::RenderWindow * AppPointer;
		Engine eng;
		ResourceManager * RMPointer;
	public:
		GameOverState(sf::RenderWindow *, ResourceManager *);
		void init();
		void draw();
		void update(float dt);
		void onSwitch();
};

#endif 

