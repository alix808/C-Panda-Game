#ifndef __Hexagon_H_INCLUDED__   
#define __Hexagon_H_INCLUDED__   
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#define R 10
#define C 10
#define RADIUS 40

class Hexagon
{
	friend class       Game;

public:

	Hexagon();

private:

	sf::CircleShape    shape[R][C];
	sf::Vector2f       position[R][C];
	sf::FloatRect      bounds[R][C];
	bool               check[R][C];
	sf::Color          color[3];

	void               setShape();
	void               hexGrid();
	void               getPosition();
	void               getBounds();
	void               checkBounds(sf::Vector2f worldPos);
	sf::Vector2f       returnCenter();
	sf::FloatRect      returnBounds();
	void               setColors();
	void               changeColor();

};

Hexagon::Hexagon()
{
	setColors();
	setShape();
	hexGrid();
	getPosition();
	getBounds();
}

void Hexagon::setShape()
{
	srand(time(NULL));
	int RandIndex = rand() % 3;
	for (int i = 0; i<R; i++) {
		for (int j = 0; j<C; j++) {
			shape[i][j].setRadius(RADIUS);
			shape[i][j].setPointCount(6);
			shape[i][j].setFillColor(sf::Color(255, 255, 255, 50));
			shape[i][j].setOutlineThickness(3);
			shape[i][j].setOutlineColor(color[1]);
		}
	}
}

void Hexagon::hexGrid()
{
	int rowNum = 0;
	int space = 0;

	do {

		for (int j = 0; j<C; j++)
		{
			if (rowNum % 2 == 0) { shape[rowNum][j].setPosition(j * 2 * RADIUS, space); }

			else if (rowNum % 2 != 0) { shape[rowNum][j].setPosition(j * 2 * RADIUS + RADIUS, space); }
		}

		rowNum = rowNum + 1;
		space = space + 70;

	} while (rowNum < R);

}

void Hexagon::getPosition()
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			position[i][j] = shape[i][j].getPosition();
}

void Hexagon::getBounds()
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			bounds[i][j] = shape[i][j].getGlobalBounds();
}

void Hexagon::checkBounds(sf::Vector2f worldPos)
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			check[i][j] = bounds[i][j].contains(worldPos.x, worldPos.y);
}

sf::Vector2f Hexagon::returnCenter()
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			if (check[i][j])
				return position[i][j];
}

sf::FloatRect Hexagon::returnBounds()
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			if (check[i][j])
				return bounds[i][j];
}

void Hexagon::setColors()
{
	color[0] = sf::Color(150, 50, 250);
	color[1] = sf::Color(250, 150, 100);
	color[2] = sf::Color::Cyan;
}

void Hexagon::changeColor()
{
	srand(time(NULL));
	int RandIndex = rand() % 3;
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
			if (check[i][j])
				shape[i][j].setFillColor(color[RandIndex]);
}


#endif

