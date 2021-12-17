#pragma once
#include <SFML/Graphics.hpp>

#include "SnakeSegment.h"
#include "Wall.h"

using namespace sf;


class Apple
{
private:
	RectangleShape sprite;
public:
	Apple();

	void setPosition(Vector2f newPosition);
	RectangleShape getSprite();
	static void moveApple(Apple& apple, vector<SnakeSegment>& snakeBody, Vector2f resolution, vector<Wall>);
};

