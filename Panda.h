#ifndef __Panda_H_INCLUDED__   
#define __Panda_H_INCLUDED__ 
#include <SFML/Graphics.hpp>
#include <iostream>

class Panda
{
	friend class Game;

public:

	Panda();

private:

	sf::Texture pandaTexture;
	sf::Texture flyTexture;
	sf::Sprite sprite;

	void loadTextures();
	void loadSprite();
	void fly();

};

Panda::Panda()
{
	loadTextures();
	loadSprite();
}

void Panda::loadTextures()
{
	if (!pandaTexture.loadFromFile("panda.png")) { cout << "Missing png file"; }
	if (!flyTexture.loadFromFile("fly.png")) { cout << "Missing png file"; }
}

void Panda::loadSprite()
{
	sprite.setTexture(pandaTexture);
}

void Panda::fly()
{
	sprite.setTexture(flyTexture);
}

#endif
