#ifndef AM_H
#define AM_H
#include <SFML/Audio.hpp>
#include <string>
using namespace std;

struct SoundBufferContainer {
	sf::SoundBuffer * sb;
	string name;
};

class AudioManager {
	public:
		AudioManager();
		void storeSoundBuffer(sf::SoundBuffer * _sb, string _name);
		sf::SoundBuffer * getSoundBuffer(string _name);
	private:
		vector<SoundBufferContainer> soundBufferList;
};

#endif
