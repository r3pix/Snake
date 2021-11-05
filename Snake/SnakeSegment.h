#pragma once
#include<sfml/Graphics.hpp>

using namespace sf;

class SnakeSegment
{
private:
	Vector2f pos;
	RectangleShape segment;



public:

	SnakeSegment(Vector2f initPos);

	Vector2f getPos();
	void setPos(Vector2f pos);

	RectangleShape getShape();

	void updatePos();

	void setColor(Color);
};

