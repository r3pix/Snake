#include "Wall.h"

Wall::Wall(Vector2f position, Vector2f size)
{
	wallShape.setSize(size);
	wallShape.setFillColor(Color::Yellow);
	wallShape.setPosition(position);
}

RectangleShape Wall::getShape()
{
	return wallShape;
}
