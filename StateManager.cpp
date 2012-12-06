//A Game State manager with State class as well
#include "StateManager.h"

//StateManager members
StateManager::StateManager(sf::RenderWindow * _app, ResourceManager * _RM, const sf::Input & _input) : Input(_input) {
	currState = 0;
	AppPointer = _app;	
	RMPointer = _RM;
	std::cout << "RMPointer Address at SM constructor: " << RMPointer << std::endl;
}

void StateManager::storeState(State * _state) {
	_state->setWindowPointer(AppPointer); //Sets reference to App window. Now as backup
	_state->setRMPointer(RMPointer); //Sets reference to RM so programmer does not have to do this often
	_state->init();
	std::cout << "RMPointer Address at storestate: " << RMPointer << std::endl;
	states.push_back(_state);
}

void StateManager::switchState(std::string _name) {
	int i = 0;
	for (i = 0; i < states.size(); i++) {
		if (states[i]->name.compare(_name) == 0) {
			std::cout << "Found it!" << std::endl;
			currState = i;
			return;
		}
	}
	throw 1;
}

void StateManager::checkSwitchState() {
	//Check current state to see if it is requesting a state change
	if (!states[currState]->switchName.empty()) {
		std::cout << "Request to change to: " << states[currState]->switchName << std::endl;
		try {
			switchState(states[currState]->switchName);
		} catch (int e) {
			std::cout << "State not found!" << std::endl;
			system("pause");
			exit(1);
		}	
	}
	return;
}

void StateManager::updateState() {
	states[currState]->update(clock.GetElapsedTime());
	clock.Reset();
}

void StateManager::drawState() {
	states[currState]->draw();
}

//State Class members


void State::init() {
	//Virtual function to act as constructor after pointers have been set
	//Pointers are set by StateManager so if the object is created outside of the SM, initial object will not have pointers
	return;
}

void State::update(float dt) {
	//Virual function to update gamestate
	return;
}

void State::draw() {
	//Virtual function to draw gamestate
	return;
}

void State::setWindowPointer(sf::RenderWindow * _ap) {
	AppPointer = _ap;
}

void State::setRMPointer(ResourceManager * _RM) {
	RMPointer = _RM;
	std::cout << "RMPointer Address at setRMPointer: " << RMPointer << std::endl;
}
