#include "SnakeControl.h"
#include "InputControl.h"

using namespace std;

void InputControl::input(RenderWindow &window,  deque<int>&directionQueue)
{
	Event event{};

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				window.close();
			}

			if (event.key.code == Keyboard::S)
			{
				addDirection(SnakeControl::Direction::UP ,directionQueue);
			}

			else if (event.key.code == Keyboard::A)
			{
				addDirection(SnakeControl::Direction::LEFT, directionQueue);
			}

			else if (event.key.code == Keyboard::W)
			{
				addDirection(SnakeControl::Direction::DOWN, directionQueue);
			}

			else if (event.key.code == Keyboard::D)
			{
				addDirection(SnakeControl::Direction::RIGHT, directionQueue);
			}

		}

	}
}

void InputControl::addDirection(int newDirection, deque<int> &directionQueue)
{
	if (directionQueue.empty())
	{
		directionQueue.emplace_back(newDirection);
	}
	else
	{
		if (directionQueue.back() != newDirection)
		{
			directionQueue.emplace_back(newDirection);
		}
	}
}