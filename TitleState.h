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

class UserPrompt : public GenericObj {
	public:
		UserPrompt(ResourceManager * _rm);
		void update(float dt);
		void draw(sf::RenderWindow * AppPointer);
	private:
		sf::Font font;
		sf::String text;
		float alpha;
		bool alphainc; //Is alpha increasing?
};

class TitleState: public State {
	private: 
		sf::Sprite titleSprite;
		const sf::Input & Input;
		Engine eng;
		DrawObj * mouse;
		//ScrollingBin sb;
	public:
		TitleState(sf::RenderWindow *);
		void init();
		void draw();
		void update(float dt);
};

#endif
