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
	Text unstartedBigText;
	Text unstartedText;

	unsigned long long score;	// deklaracja wyniku
	Text scoreText;
	
	deque<int> directionQueue;
	int sectionsToAdd;

	int currentGameState;
	int lastGameState;

	Apple apple;	// stworzenie nowego obiektu klasy Apple
	int applesEaten;	// deklaracja licznika zjedzonych jablek
	int applesTotal;	// deklaracja licznika wszystkich jablek jakie sie pojawily podczas rozgrywki
	Text applesText;
	Text currentLevelText;

	vector<Wall> walls;
	
	
	vector<string> levels;

	Font mainFont;
	Text titleText;

public:
	enum  GameState {RUNNING, PAUSED, GAMEOVER,UNSTARTED};
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

