#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(Vector2f initPos)
{
	segment.setSize(Vector2f(15, 15));
	segment.setFillColor(Color::Cyan);
	segment.setPosition(initPos);
	pos = initPos;
}


Vector2f SnakeSegment::getPos()
{
	return pos;
}

void SnakeSegment::setPos(Vector2f pos)
{
	this->pos = pos;
}

RectangleShape SnakeSegment::getShape()
{
	return segment;
}

void SnakeSegment::updatePos()
{
	segment.setPosition(pos);
}

void SnakeSegment::setColor(Color color)
{
	segment.setFillColor(color);
}