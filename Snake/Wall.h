#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
private:
	RectangleShape wallShape;	// obiekt ksztaltu sciany

public:
	Wall(Vector2f position, Vector2f size);

	RectangleShape getShape();	// getter ksztaltu scian
};

