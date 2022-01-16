#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "SnakeSegment.h"
#include <vector>
#include <deque>
#include "Apple.h"
#include "Wall.h"
#include <fstream>

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
	Text gameOverText;
	Text pressButtonText;
	Text pauseText;
	Text pauseBigText;

	unsigned long long score;
	Text scoreText;
	
	deque<int> directionQueue;
	int sectionsToAdd;

	int currentGameState;
	int lastGameState;

	Apple apple;
	int applesEaten;
	int applesTotal;
	Text applesText;
	Text currentLevelText;

	vector<Wall> walls;
	
	
	vector<string> levels;

	Font mainFont;
	Text titleText;

public:
	enum  GameState {RUNNING, PAUSED, GAMEOVER};
	int currentLevel;
	int maxLexels;

	Engine();
	void draw();
	void run();
	void beginNextLevel();
	void startTheGame();
	void moveApple();
	static void togglePause(int& currentGameState, int& lastGameState);

	void checkLevelFiles();
	void loadLevel(int levelNumber);

	static void setupText(Text* textItem, const Font& font, const String& value, int size, Color color);
};

