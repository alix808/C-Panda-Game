#ifndef __Audio_H_INCLUDED__   
#define __Audio_H_INCLUDED__   
#include <SFML/Audio.hpp>
#include <iostream>

class Audio
{
	friend class Game;

public:

	Audio();

private:

	sf::SoundBuffer buffer;
	sf::Sound sound;

	void loadBuffer();
	void loadSound();

};

Audio::Audio()
{   
	loadBuffer();
	loadSound();
}

void Audio::loadBuffer()
{
	if (!buffer.loadFromFile("sound.wav"))
	{
		cout << "Missing audio file";
	}
}

void Audio::loadSound()
{
	sound.setBuffer(buffer);
}


#endif
