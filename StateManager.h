#ifndef SM_H
#define SM_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/graphics.hpp>
#include "ResourceManager.h"

class State {
	protected:
		sf::RenderWindow * AppPointer;
		ResourceManager * RMPointer;
	public:
		virtual void init(); //REMEMBER: it is important to have these functions declared as State::Function (even if it is only "return;" and they will be redeclared)
		virtual void update(float dt);
		virtual void draw();
		void setWindowPointer(sf::RenderWindow *); //Set the pointer to the RenderWindow for draw()
		void setRMPointer(ResourceManager *); //Set pointer to ResourceManager 
		
		std::string name;
		std::string switchName; //If this is not "" then this state is calling for a change of state
};

class StateManager {
	private:
		int currState;
		std::vector<State *> states;
		sf::RenderWindow * AppPointer; 
		ResourceManager * RMPointer;
		const sf::Input & Input; //Does SM really need this?
		sf::Clock clock;
	public:
		StateManager(sf::RenderWindow *, ResourceManager *, const sf::Input &);
		void storeState(State *);
		void switchState(std::string);
		void checkSwitchState();
		void updateState();
		void drawState();
};

#endif
