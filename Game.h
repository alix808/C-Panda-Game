#ifndef __Game_H_INCLUDED__   
#define __Game_H_INCLUDED__ 
#include <SFML/Graphics.hpp>
#include "Hexagon.h"
#include "Panda.h"
#include "Audio.h"
#include <iostream>
using namespace std;

class Game : private sf::NonCopyable
{
    
    public:

	Game();
	void                run();

    private:

	Hexagon             hex;
	Panda               panda;
	Audio               audio;
	sf::Time            TimePerFrame;
	sf::VideoMode       desktop;
	sf::RenderWindow    mWindow;
	int                 width;
	int                 height;

	sf::Vector2f        worldPos;
	sf::Vector2f        delta;
	sf::FloatRect       tileBounds;
	bool                pIsMoving;
	bool                check;

	void                processEvents();
	void                update(sf::Time elapsedTime);
	void                render();
	void                drawHex();
	void                getCoordinates();

};


Game::Game()
	: mWindow(sf::VideoMode(desktop.getDesktopMode()), "SFML Application", sf::Style::None)
	, width(desktop.getDesktopMode().width)
	, height(desktop.getDesktopMode().height)
	, pIsMoving(false)
	, hex()
	, panda()
	, audio()
	, TimePerFrame(sf::seconds(1.f / 60.f))
{
	panda.sprite.setPosition(hex.position[12][0].x + 10, hex.position[12][0].y + 10);

	sf::View view(sf::FloatRect(0, 0, width, height));
	view.setCenter(sf::Vector2f(hex.position[R / 2][C / 2]));
	view.setRotation(45);
	mWindow.setView(view);

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
		{
			pIsMoving = true;
			panda.fly();
			audio.sound.play();
			getCoordinates();
		}

		else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			mWindow.close();
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	if (tileBounds.contains(panda.sprite.getPosition().x, panda.sprite.getPosition().y))
	{
		panda.sprite.setPosition(worldPos.x + 15, worldPos.y + 10);
		pIsMoving = false;
		audio.sound.stop();
		panda.loadSprite();
		hex.changeColor();
	}

	else if (pIsMoving)
	{
		for (int i = 0; i<R; i++)
			for (int j = 0; j<C; j++)
				if (hex.check[i][j])
					panda.sprite.move(delta * elapsedTime.asSeconds());
	}
}

void Game::render()
{
	mWindow.clear();
	drawHex();
	mWindow.draw(panda.sprite);
	mWindow.display();
}

void Game::drawHex()
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			mWindow.draw(hex.shape[i][j]);
}

void Game::getCoordinates()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
	worldPos = mWindow.mapPixelToCoords(mousePos);
	sf::Vector2f currentPos = panda.sprite.getPosition();
	hex.checkBounds(worldPos);
	worldPos = hex.returnCenter();
	delta = worldPos - currentPos;
	delta.x += 20;
	delta.y += 20;
	tileBounds = hex.returnBounds();
}

#endif
