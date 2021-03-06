#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "StateManager.h"
#include "TitleState.h"
#include "LoaderState.h"
#include "GameState.h"
#include "GameOverState.h"
#include <typeinfo>
#include <cstdio>

//If you see a white pixel that is supposed to be an image, try looking to see if sprite has image linked
int main(void) {
	
	//Buffer for output stream
	//This makes output faster at a cost of being unsure when it is output
	//Because the flush to OS function is expensive
	char buf[1024];
	//setvbuf(stdout, buf, _IOLBF, 1024);
	//Main function
	
	
	//Setup game objs
	sf::RenderWindow App(sf::VideoMode(800,600,32), "Satellite Game"); //Make the window
	//App.ShowMouseCursor(false); //Hide the cursor 
	ResourceManager RM; //Make RM

	//Make a pointer to the window and RM to pass to StateManager
	sf::RenderWindow *AppPointer = &App;
	ResourceManager * RMPointer = &RM;

	const sf::Input & Input = App.GetInput(); //Make Input 
	StateManager SM(AppPointer, RMPointer, Input);  //Make StateManager

	App.SetFramerateLimit(30); //Limit Framerate to standard refresh rate
	
	//Should probably make a loader state for loading resources at beginning
	//Then calls switchstate to title
	//This doesn't even need to have a display, just make sure it is initialized 
	//	The init() function will load everything
	LoaderState LS; 
	SM.storeState(&LS);
	
	//TitleStateTesting
	//Make TitleState
	TitleState TS(AppPointer); //This should passed AppPointer instead of input, as input can be found with AppPointer
	SM.storeState(&TS);
	
	//Make GameState
	GameState GS(AppPointer, RMPointer);
	SM.storeState(&GS);
	
	//Make GameOverState
	GameOverState GOS(AppPointer, RMPointer);
	SM.storeState(&GOS);
	
	try {
		SM.switchState("Title");
	} catch (int e) {
		std::cout << "Could not find state title" << std::endl;
	}
	std::cout << "Switched States" << std::endl;
	//EndTS Testing
	
	//Start game loop
	while (App.IsOpened()) {
		//Get events
		sf::Event Event;
		while (App.GetEvent(Event)) { //Iterate thru event queue, store events in Event and process
			if (Event.Type == sf::Event::Closed || (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)) {
				App.Close();
				//std::cout << "I died here?" << std::endl;
				exit(0); // Strange... I didn't need this before (this is to prevent crash after closing)
				//return 0;
				//std::cout << "Nothing here!" << std::endl;
			} 
			//else if (Event.Type == sf::Event::MouseMoved) {
			//	std::cout << "The mouse moved!" << std::endl;
			//}
		}
		App.Clear(); //Clear screen
		//App.Draw(s);
		SM.checkSwitchState();
		SM.updateState();
		SM.drawState();
		App.Display(); //Update Screen
	}
	return 0;
}
