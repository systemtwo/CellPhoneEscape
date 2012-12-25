#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() {
	return;
}

void AudioManager::storeSoundBuffer(sf::SoundBuffer * _sb, string _name) {
	SoundBufferContainer sbc;
	sbc.sb = _sb;
	sbc.name = _name;
	
	soundBufferList.push_back(sbc);
	return;
}

sf::SoundBuffer * AudioManager::getSoundBuffer(string _name) {
	for (int i = 0; i < soundBufferList.size(); i++) {
		if (soundBufferList[i].name == _name) {
			cout << "Got it!";
			return soundBufferList[i].sb;
		}
	}
	throw 1;
}
