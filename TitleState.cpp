#include "TitleState.h"
#include <cmath>

ScrollingBin::ScrollingBin(ResourceManager * _rm) : GenericObj() {
	sprite.SetX(0);
	sprite.SetY(rand()%500);
	sprite.SetImage(*_rm->getImage("binary"));
	return;
}

void ScrollingBin::update(float dt) {
	sprite.SetX(floor(x));
	x += dt* 30;
	//sprite.Move (floor(dt*10), 0);
	return;
}

void ScrollingBin::draw(sf::RenderWindow * AppPointer) {
	//sprite.SetX(100);
	//sprite.SetY (100);
	std::cout << "I am being called" << std::endl;
	AppPointer->Draw(sprite);
	return;
}

TitleState::TitleState(const sf::Input & _input) : Input(_input) {
	//RMPointer has not been set yet at this point!
	name = "Title";
	return;
}

void TitleState::init() {
	try {
		titleSprite.SetImage(*RMPointer->getImage("title"));
	} catch (int e) {
		std::cout << "Could not find image" << std::endl;
	}	
	eng.setAppPointer(AppPointer);
	sf::Sprite * tmp = new sf::Sprite;
	tmp->SetImage(*RMPointer->getImage("pointer"));
	mouse = eng.makeAndAddObj(tmp, 20);
	eng.addGenObj(new ScrollingBin(RMPointer));
	//sb.sprite.SetImage(*RMPointer->getImage("binary"));
	//eng.makeAndAddObj(&sb.sprite, 1);
}

void TitleState::update(float dt) {
	int mouseXShift = mouse->sprite->GetSize().x;
	int mouseYShift = mouse->sprite->GetSize().y;
	mouse->sprite->SetX(Input.GetMouseX()-(mouseXShift/2));
	mouse->sprite->SetY(Input.GetMouseY()-(mouseYShift/2));
	std::cout <<"FPS: " << 1/dt << std::endl;
	if (Input.IsMouseButtonDown(sf::Mouse::Left)) {
		switchName = "Game";
	}
	//sb.update(dt);
	eng.updateAllGenObj(dt);
}

void TitleState::draw() {
	eng.drawAll();
	eng.drawAllGenObj();
	return;
}
