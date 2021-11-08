#pragma once
#include <deque>
#include <vector>
#include <SFML/System/Time.hpp>
#include "SnakeSegment.h"

using namespace std;
using namespace sf;

class SnakeControl
{
private:
	//int directionCode;

public:
	static void updateDirection(vector<SnakeSegment>& snakeBody, deque<int>& directionQueue, int speed, int &directionCode, Time &timeSinceLastMove);

	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
};