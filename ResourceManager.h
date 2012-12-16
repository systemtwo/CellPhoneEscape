#ifndef RM_H
#define RM_H

#include <string>
#include <vector>
#include <iostream>
#include <SFML/graphics.hpp>


struct Resource {
	sf::Image * image;
	std::string name;
};

class ResourceManager {
	private:
		std::vector<Resource *> storage;
	public:
		//Constructor and Destructor
		ResourceManager();
		sf::Image * getImage(std::string); //NOTE: This will return a pointer to the image
		void storeImage(sf::Image *, std::string);
		void deleteImage(std::string);
};

#endif
