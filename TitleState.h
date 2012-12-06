#ifndef TS_H
#define TS_H

#include <iostream>
#include <SFML/graphics.hpp>
#include <vector>
#include "StateManager.h"
#include "Engine.h"
#include "ResourceManager.h"



class ScrollingBin : public GenericObj {
	public:
		ScrollingBin(ResourceManager * _rm);
		sf::Sprite sprite;
		void update(float dt);
		void draw(sf::RenderWindow * AppPointer);
		float x, y;
	private:
		
};

class TitleState: public State {
	private: 
		sf::Sprite titleSprite;
		const sf::Input & Input;
		Engine eng;
		DrawObj * mouse;
		//ScrollingBin sb;
	public:
		TitleState(const sf::Input &);
		void init();
		void draw();
		void update(float dt);
};

#endif
