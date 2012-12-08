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
	if (x > 300) {
		selfDestruct();
	}
	//sprite.Move (floor(dt*10), 0);
	return;
}

void ScrollingBin::draw(sf::RenderWindow * AppPointer) {
	AppPointer->Draw(sprite);
	return;
}

UserPrompt::UserPrompt(ResourceManager * _rm) {
	font.LoadFromFile("snr.ttf");
	text.SetFont(font);
	text.SetSize(20);
	text.SetText("Press Space to begin");
	
	text.SetX(300);
	text.SetY(400);
}

void UserPrompt::update(float dt) {
	if (alpha >= 255) {
		alphainc = false;
	} else if (alpha <= 0) {
		alphainc = true;
	}
	if (alphainc) {
		alpha += 40* dt;
	} else {
		alpha -= 40* dt;
	}
	
	//Check for overshoot of alpha
	if (alphainc && alpha > 255) {
		alpha = 255;
	} else if ((!alphainc) && alpha < 0) {
		alpha = 0;
	}
	text.SetColor(sf::Color(255, 255, 255, alpha));
}

void UserPrompt::draw(sf::RenderWindow * _ap) {
	_ap->Draw(text);
	return;
}


TitleState::TitleState(sf::RenderWindow * _ap) : Input(_ap->GetInput()) {
	//RMPointer has not been set yet at this point!
	AppPointer = _ap;
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
	//sf::Sprite * tmp = new sf::Sprite;
	//tmp->SetImage(*RMPointer->getImage("pointer"));
	//mouse = eng.makeAndAddObj(tmp, 20);
	eng.addGenObj(new ScrollingBin(RMPointer));
	eng.addGenObj(new UserPrompt(RMPointer));
	eng.addGenObj(new FPSDisplay);
}

void TitleState::update(float dt) {
	/* Mouse is removed for this game
	int mouseXShift = mouse->sprite->GetSize().x;
	int mouseYShift = mouse->sprite->GetSize().y;
	mouse->sprite->SetX(Input.GetMouseX()-(mouseXShift/2));
	mouse->sprite->SetY(Input.GetMouseY()-(mouseYShift/2));
	*/
	if (Input.IsMouseButtonDown(sf::Mouse::Left)) {
		switchName = "Game";
	} 
	if (Input.IsKeyDown(sf::Key::Space)) {
		switchName = "Game";
	}
	//sb.update(dt);
	eng.updateAllGenObj(dt);
}

void TitleState::draw() {
	AppPointer->Draw(titleSprite);
	//eng.drawAll();
	eng.drawAllGenObj();
	return;
}
