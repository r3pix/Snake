#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "SnakeSegment.h"
#include <vector>
#include <deque>
#include "Apple.h"


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
	Time timeSinceLastMove;
	
	deque<int> directionQueue;
	int sectionsToAdd;

	int currentGameState;
	int lastGameState;

	Apple apple;

public:
	enum  GameState {RUNNING, PAUSED, GAMEOVER};

	Engine();
	void draw();
	void run();
	void startTheGame();
	void moveApple();
	static void togglePause(int& currentGameState, int& lastGameState);
};

