#pragma once
#include <deque>
#include <vector>
#include <SFML/System/Time.hpp>

#include "Apple.h"
#include "Engine.h"
#include "SnakeSegment.h"

using namespace std;
using namespace sf;

class SnakeControl
{
private:
	//int directionCode;

public:
	// funkcja zmieniajaca kierunek poruszania sie weza
	static void updateDirection(vector<SnakeSegment>& snakeBody, deque<int>& directionQueue, int speed, int &directionCode, Time &timeSinceLastMove, 
		Apple &apple, int &sectionsToAdd, Vector2f resolution,int& currentGameState,vector<Wall>walls, int &applesTotal, int& applesEaten, unsigned long long &score, Engine& engine);

	enum  GameState { RUNNING, PAUSED, GAMEOVER };	// enum z wszystkimi mnozliwymi stanami gry

	enum Direction	// enum z wszystkimi mozliwymi kierunkami porusznaia sie weza
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
};