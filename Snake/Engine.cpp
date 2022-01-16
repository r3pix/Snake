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

	mainFont.loadFromFile("Deargod.otf");
	setupText(&titleText,mainFont,"SNAKE",28,Color::Cyan);
	FloatRect titleTextBounds = titleText.getLocalBounds();
	titleText.setPosition(Vector2f(resolution.x/2 - titleTextBounds.width /2, -9));

	setupText(&currentLevelText, mainFont, "Level 1", 28, Color::Red);
	currentLevelText.setPosition(Vector2f(15,-9));
	FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();


	setupText(&applesText, mainFont, "Apples 0", 28, Color::Red);
	applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width+20,-9));

	setupText(&scoreText, mainFont, to_string(score), 28, Color::Red);
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

	setupText(&gameOverText, mainFont, "GAME OVER!", 75, Color::Green);
	FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	gameOverText.setPosition(Vector2f(resolution.x/2 - gameOverTextBounds.width/2, 100));
	gameOverText.setOutlineColor(Color::Black);
	gameOverText.setOutlineThickness(3);


	setupText(&pressButtonText, mainFont, "Press R to restart", 38, Color::Green);
	FloatRect pressButtonTextBounds = pressButtonText.getLocalBounds();
	pressButtonText.setPosition(Vector2f(resolution.x / 2 - pressButtonTextBounds.width / 2, 200));
	pressButtonText.setOutlineColor(Color::Black);
	pressButtonText.setOutlineThickness(2);


	setupText(&pauseBigText, mainFont, "GAME PAUSED!", 75, Color::Green);
	FloatRect pauseBigTextBounds = pauseBigText.getLocalBounds();
	pauseBigText.setPosition(Vector2f(resolution.x / 2 - pauseBigTextBounds.width / 2, 100));
	pauseBigText.setOutlineColor(Color::Black);
	pauseBigText.setOutlineThickness(3);

	setupText(&pauseText, mainFont, "Press P to continue", 38, Color::Green);
	FloatRect pauseTextBounds = pauseText.getLocalBounds();
	pauseText.setPosition(Vector2f(resolution.x / 2 - pauseTextBounds.width / 2, 200));
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(2);

	run();

}

void Engine::startTheGame()
{
	score = 0;
	sectionsToAdd = 0;
	speed = 2;
	directionCode = SnakeControl::Direction::RIGHT;
	timeSinceLastMove = Time::Zero;
	directionQueue.clear();
	walls.clear();
	applesEaten = 0;
	applesTotal = 0;
	currentLevel = 1;
	loadLevel(currentLevel);
	SnakeSegment::createSnake(snakeBody);
	Apple::moveApple(apple, snakeBody, resolution, walls);
	currentGameState = GameState::RUNNING;
	lastGameState = currentGameState;
	currentLevelText.setString("Level "+to_string(currentLevel));
	applesText.setString("Apples " + to_string(applesTotal));
	scoreText.setString("Score " + to_string(score));

	FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
	applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));
	

}


void Engine::beginNextLevel()
{
	currentLevel += 1;
	walls.clear();
	directionQueue.clear();

	speed = 2 + currentLevel;
	directionCode = SnakeControl::Direction::RIGHT;
	sectionsToAdd = 0;
	applesEaten = 0;

	loadLevel(currentLevel);
	SnakeSegment::createSnake(snakeBody);
	Apple::moveApple(apple, snakeBody, resolution, walls);

	currentLevelText.setString("Level " + to_string(currentLevel));

	FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
	applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

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

	window.draw(titleText);
	window.draw(currentLevelText);
	window.draw(applesText);
	window.draw(scoreText);

	if (currentGameState == GameState::GAMEOVER)
	{
		
		window.draw(gameOverText);
		window.draw(pressButtonText);
	}
	if (currentGameState == GameState::PAUSED)
	{
		//draw();
		window.draw(pauseBigText);
		window.draw(pauseText);

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


void Engine::setupText(Text* textItem, const Font& font, const String& value, int size, Color color)
{
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(color);

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
		SnakeControl::updateDirection(snakeBody,directionQueue, speed, directionCode, timeSinceLastMove, apple, sectionsToAdd, resolution, currentGameState,walls,
			applesTotal,applesEaten,score, *this);
		applesText.setString("Apples " + to_string(applesTotal));
		FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
		applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

		scoreText.setString("Score " + to_string(score));
		FloatRect scoreTextBounds = scoreText.getLocalBounds();
		scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

		//if()

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