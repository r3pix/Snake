#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "SnakeSegment.h"
#include <vector>
#include <deque>


using namespace sf;
using namespace std;


class Engine
{
private:
	Vector2f resolution;
	RenderWindow window;
	const unsigned int fps = 60;
	static const Time TimePerFrame;
	vector<SnakeSegment> snakeBody;
	RectangleShape backgroud;

	int directionCode;
	int speed;
	deque<int> directionQueue;

	Time timeSinceLastMove;

public:
	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Engine();
	void input();
	void draw();
	void run();

	void createSnake();
	void addSegment();

	void addDirection(int newDirection);
	void updateDirection();

};

