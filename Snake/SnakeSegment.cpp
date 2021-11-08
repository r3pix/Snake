#include "SnakeSegment.h"

using namespace std;

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

void SnakeSegment::createSnake(vector<SnakeSegment> &snakeBody)
{
	snakeBody.clear();
	snakeBody.emplace_back(Vector2f(100, 100));
	snakeBody[0].setColor(Color::Red);
	snakeBody.emplace_back(Vector2f(80, 100));
	snakeBody.emplace_back(Vector2f(60, 100));
}

void SnakeSegment::addSegment(vector<SnakeSegment>& snakeBody)
{
	Vector2f newPos = snakeBody[snakeBody.size() - 1].getPos();
	snakeBody.emplace_back(Vector2f(newPos));
}