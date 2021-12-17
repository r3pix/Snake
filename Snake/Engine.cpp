#include "Engine.h"
#include "InputControl.h"
#include "SnakeControl.h"


const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine()
{
	resolution = Vector2f(800, 600);
	window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
	window.setFramerateLimit(fps);
	backgroud.setSize(Vector2f(800, 600));
	backgroud.setFillColor(Color(169,169,169));
	maxLexels = 0;
	checkLevelFiles();

	startTheGame();

}

void Engine::startTheGame()
{
	sectionsToAdd = 0;
	speed = 2;
	directionCode = SnakeControl::Direction::RIGHT;
	timeSinceLastMove = Time::Zero;
	directionQueue.clear();
	currentLevel = 1;
	loadLevel(currentLevel);
	SnakeSegment::createSnake(snakeBody);
	Apple::moveApple(apple, snakeBody, resolution, walls);
	currentGameState = GameState::RUNNING;
	lastGameState = currentGameState;
}


void Engine::draw()
{
	window.clear();
	window.draw(backgroud);
	//window.clear(Color::Black);
	for(auto &w:walls)
	{
		window.draw(w.getShape());
	}

	window.draw(apple.getSprite());

	for(auto &s: snakeBody)
	{
		window.draw(s.getShape());
	}

	window.display();
}

void Engine::checkLevelFiles()
{
	ifstream levelsManifest("levels.txt");

	ifstream testFile;
	for(string manifestLine; getline(levelsManifest,manifestLine);)
	{
		testFile.open(manifestLine);
		if(testFile.is_open())
		{
			levels.emplace_back(manifestLine);
			testFile.close();
			maxLexels++;
		}
	}
}

void Engine::loadLevel(int levelNumber)
{
	string levelFile = levels[levelNumber - 1];
	ifstream level(levelFile);
	string line;
	if(level.is_open())
	{
		for(int y=0; y<30; y++)
		{
			getline(level, line);
			for(int x=0; x<40; x++)
			{
				if(line[x]=='x')
				{
					walls.emplace_back(Wall(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
				}
			}
		}
	}
	level.close();
}


/*
void Engine::moveApple()
{
	Vector2f appleResolution = Vector2f(resolution.x / 15 - 2, resolution.y / 15 - 2);
	Vector2f newLocation;
	bool isLocationFine = true;
	srand(time(NULL));
	do
	{
		isLocationFine = true;
		newLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 15;
		newLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 15;

		for(auto &s : snakeBody)
		{
			if(s.getShape().getGlobalBounds().intersects(Rect<float>(newLocation.x,newLocation.y,20,20)))
			{
				isLocationFine = false;
				break;
			}

		}
	} while (!isLocationFine);

	apple.setPosition(newLocation);
}
*/

void Engine::run()
{
	Clock clock;

	while (window.isOpen())
	{
		Time between = clock.restart();

		if(currentGameState == GameState::PAUSED || currentGameState==GameState::GAMEOVER)
		{
			InputControl::input(window, directionQueue,currentGameState,lastGameState, *this);

			if(currentGameState==GameState::GAMEOVER)
			{
				draw();
			}

			sleep(milliseconds(2));
			continue;

		}

		timeSinceLastMove = timeSinceLastMove + between;

		InputControl::input(window,directionQueue,currentGameState,lastGameState,*this);
		SnakeControl::updateDirection(snakeBody,directionQueue, speed, directionCode, timeSinceLastMove, apple, sectionsToAdd, resolution, currentGameState,walls);
		draw();
	}
}
/*
void Engine::togglePause(int &currentGameState, int &lastGameState)
{
	if(currentGameState == GameState::RUNNING)
	{
		lastGameState = currentGameState;
		currentGameState = GameState::PAUSED;
	}
	else if(currentGameState == GameState::PAUSED)
	{
		currentGameState = lastGameState;
	}
}
*/