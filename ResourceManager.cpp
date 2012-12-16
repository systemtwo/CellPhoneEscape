#include "ResourceManager.h" //Remember to always include its own .h file first

#include <typeinfo>

ResourceManager::ResourceManager() {
	//Do nothing for now
}

sf::Image * ResourceManager::getImage(std::string _name) {
	//Retrieves a sf::Sprite from storage
	int i = 0;
	for (i = 0; i < storage.size(); i++) {
		//std::cout << "I'm in loop at" << i << std::endl;
		//std::cout << "Address: " << &storage << std::endl;
		//std::cout << typeid(storage[i]->name).name() << std::endl;
		
		if ((storage[i]->name).compare(_name) == 0) {
			//Strings are the same
			return storage[i]->image;
		}
		
	}
	throw 1;
}

void ResourceManager::storeImage(sf::Image * _image, std::string _name) {
	//Stores an image
	//Name should have something to do with the type of resource (image or sound)
	//Should this be a pointer?
	Resource * r = new Resource;
	r->image = _image;
	r->name = _name;
	
	r->image->SetSmooth(false);
	storage.push_back(r);
}

void ResourceManager::deleteImage(std::string _name ) {
	int i = 0;
	for (i = 0; i < storage.size(); i++) {
		//std::cout << "I'm in loop at" << i << std::endl;
		//std::cout << "Address: " << &storage << std::endl;
		//std::cout << typeid(storage[i]->name).name() << std::endl;
		
		if ((storage[i]->name).compare(_name) == 0) {
			//Strings are the same
			delete storage[i];
			storage.erase(storage.begin() + i);
		}
		
	}
	throw 1;
	return;
}


