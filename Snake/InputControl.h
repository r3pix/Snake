#pragma once

class InputControl
{
public:
	static void input(RenderWindow& window, deque<int>& directionQueue);
	static void addDirection(int newDirection, deque<int>& directionQueue);
};