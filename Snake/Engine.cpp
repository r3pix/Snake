#include "Engine.h"
#include "InputControl.h"
#include "SnakeControl.h"


const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

/**
  * \brief Glowna klasa Engine
  */
Engine::Engine()
{
	resolution = Vector2f(800, 600);	// ustawienie rozdzielczosci okna gry
	window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);	// utworzenie okna
	window.setFramerateLimit(fps);	// uistawienie limitu klatek na sekunde
	backgroud.setSize(Vector2f(800, 600));	// ustawienie rozmiaru okna
	backgroud.setFillColor(Color(169,169,169));	// ustawienie koloru tla
	maxLexels = 0;
	checkLevelFiles();	// saprawdzenie plikow z poziomami

	startTheGame();	// uruchomienie gry

	mainFont.loadFromFile("Deargod.otf");	// zaladowanie pliku z czcionkami
	setupText(&titleText,mainFont,"SNAKE",28,Color::Cyan);	// ustawienie parametrow naglowka
	FloatRect titleTextBounds = titleText.getLocalBounds();	// getter dlugosci napisu
	titleText.setPosition(Vector2f(resolution.x/2 - titleTextBounds.width /2, -9));	// ustawienie pozycji napisu

	setupText(&currentLevelText, mainFont, "Level 1", 28, Color::Red);	// wyswietlenie informacji o rozpoczeciu sie pierwszego poziomu
	currentLevelText.setPosition(Vector2f(15,-9));	// ustawienie pozcji tekstu z informacja o aktualnym poziomie
	FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();	// getter dlugosci napisu


	setupText(&applesText, mainFont, "Apples 0", 28, Color::Red);	// ustawienie parametrow jablka (ilosc zebranych jablek, kolor jablka itp)
	applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width+20,-9));	// ustawienie pozycji tekstu

	setupText(&scoreText, mainFont, to_string(score), 28, Color::Red);	// ustawienie parametrow tekstu z informacja o wyniku
	FloatRect scoreTextBounds = scoreText.getLocalBounds();	// getter dlugosci napisu
	scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));	// ustawienie pozycji wyniku

	setupText(&gameOverText, mainFont, "GAME OVER!", 75, Color::Green);	// ustawienie parametrow informacji o koncu gry
	FloatRect gameOverTextBounds = gameOverText.getLocalBounds();	// getter dlugosci napisu
	gameOverText.setPosition(Vector2f(resolution.x/2 - gameOverTextBounds.width/2, 100));	// ustawienie pozycji teklstu
	gameOverText.setOutlineColor(Color::Black);	// ustawienie koloru obwodki tekstu na czarny
	gameOverText.setOutlineThickness(3);	// ustawienie grubosci granic


	setupText(&pressButtonText, mainFont, "Press R to restart", 38, Color::Green);	// ustawienie parametrow informacji o ponownej probie gry
	FloatRect pressButtonTextBounds = pressButtonText.getLocalBounds();	// getter dlugosci napisu
	pressButtonText.setPosition(Vector2f(resolution.x / 2 - pressButtonTextBounds.width / 2, 200));	// ustawieie pozycji tekstu
	pressButtonText.setOutlineColor(Color::Black);	// ustawienie koloru obwodki tekstu na czarny
	pressButtonText.setOutlineThickness(2);		// ustawienie grubosci granic


	setupText(&pauseBigText, mainFont, "GAME PAUSED!", 75, Color::Green);
	FloatRect pauseBigTextBounds = pauseBigText.getLocalBounds();
	pauseBigText.setPosition(Vector2f(resolution.x / 2 - pauseBigTextBounds.width / 2, 100));
	pauseBigText.setOutlineColor(Color::Black);	// ustawienie koloru obwodki tekstu na czarny
	pauseBigText.setOutlineThickness(3);	// ustawienie grubosci granic

	setupText(&pauseText, mainFont, "Press P to continue", 38, Color::Green);
	FloatRect pauseTextBounds = pauseText.getLocalBounds();
	pauseText.setPosition(Vector2f(resolution.x / 2 - pauseTextBounds.width / 2, 200));
	pauseText.setOutlineColor(Color::Black);	// ustawienie koloru obwodki tekstu na czarny
	pauseText.setOutlineThickness(2);	// ustawienie grubosci granic

	setupText(&unstartedBigText, mainFont, "GAME UNSTARTED!", 75, Color::Green);
	FloatRect unstartedBigTextBounds = unstartedBigText.getLocalBounds();
	unstartedBigText.setPosition(Vector2f(resolution.x / 2 - unstartedBigTextBounds.width / 2, 100));
	unstartedBigText.setOutlineColor(Color::Black);	// ustawienie koloru obwodki tekstu na czarny
	unstartedBigText.setOutlineThickness(3);	// ustawienie grubosci granic

	setupText(&unstartedText, mainFont, "Press N to start", 38, Color::Green);
	FloatRect unstartedTextBounds = unstartedText.getLocalBounds();
	unstartedText.setPosition(Vector2f(resolution.x / 2 - unstartedTextBounds.width / 2, 200));
	unstartedText.setOutlineColor(Color::Black);	// ustawienie koloru obwodki tekstu na czarny
	unstartedText.setOutlineThickness(2);	// ustawienie grubosci granic


	run();

}

/**
  * \brief Metoda uruchamiajaca gre
  */
void Engine::startTheGame()
{
	score = 0;	// ustawienie wyniku na 0
	sectionsToAdd = 0;	// wyzerowanie licznika dodanych czesci
	speed = 2;	// ustawienie wartosci predkosci poruszania sie weza na 2
	directionCode = SnakeControl::Direction::RIGHT;	// ustawienie poczatkowego kierunku poruszania sie weza na w prawo
	timeSinceLastMove = Time::Zero;	// wyzerowanie czasu
	directionQueue.clear();	// wyczyszczenie kolejki zapisujacej ruchy
	walls.clear();	// wyczyszczenie mapy
	applesEaten = 0;	// wyzerowanie licznika zjedzonych jablek
	applesTotal = 0;	// wyzerowanie wszystkich jablek ktore sie pojawily w rozgrywce
	currentLevel = 1;	// ustawienie poziomu na pierwszy
	loadLevel(currentLevel);	// zaladowanie poziomu
	SnakeSegment::createSnake(snakeBody);	// utworzenie weza
	Apple::moveApple(apple, snakeBody, resolution, walls);	// utworzenie jablka
	currentGameState = GameState::UNSTARTED;	// zmiana stanu gry
	lastGameState = GameState::RUNNING;		// przypisanie aktualnego stanu gry pod poprzedni
	currentLevelText.setString("Level "+to_string(currentLevel));	// wyswietlenie informacji o poziomie
	applesText.setString("Apples " + to_string(applesTotal));	// wyswietlenie informacji o zebranych jablkach
	scoreText.setString("Score " + to_string(score));	// wyswietlenie informacji o wyniku

	FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
	applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));	// ustawienie pozycji tekstu o jakblkach
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));	// ustawienie pozycji tekstu z wynikiem
	

}

/**
  * \brief Metoda rozpoczynajaca kolejny poziom
  */
void Engine::beginNextLevel()
{
	currentLevel += 1;	// zwiekszenie wartosci zmiennej z aktualnym poziomem
	walls.clear();	// wyczyszczenie mapy
	directionQueue.clear();	// wyczyszczenie kolejki z ruchami

	speed = 2 + currentLevel;	// zwiekszenie predkosci poruszania sie weza
	directionCode = SnakeControl::Direction::RIGHT;	// ustawienie poczatkowego kierunku poruszania sie weza
	sectionsToAdd = 0;	// wyzerowanie licznika dodanych czesci
	applesEaten = 0;	// wyzerowanie licznika zjedzonych jablek

	loadLevel(currentLevel);	// zaladowanie nastepnego poziomu
	SnakeSegment::createSnake(snakeBody);	// utworzenie weza
	Apple::moveApple(apple, snakeBody, resolution, walls);	// utworzenie jablka

	currentLevelText.setString("Level " + to_string(currentLevel));	// informacja o aktualnym poziomie

	FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
	applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));	// ustawienie pozycji tekstu o jablkach
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));	// ustawienie pozycji tekstu z wynikiem

}

/**
  * \brief Metoda rysujaca gre
  */
void Engine::draw()
{
	window.clear();	// wyczyszczenie okna
	window.draw(backgroud);	// narysowanie tla
	//window.clear(Color::Black);
	for(auto &w:walls)
	{
		window.draw(w.getShape());	// rysowanie scian
	}

	window.draw(apple.getSprite());	// rysowanie jablka

	for(auto &s: snakeBody)
	{
		window.draw(s.getShape());	// rysowanie ciala weza
	}

	window.draw(titleText);	// rysowanie tytulu
	window.draw(currentLevelText);	// rysowanie tekstu z aktualnym poziomem rozgrywki
	window.draw(applesText);	// rysowanie tekstu z liczba jablek
	window.draw(scoreText);	// rysowanie tekstu z wynikiem

	if (currentGameState == GameState::GAMEOVER)	// jesli stan gry to GAMEOVER
	{
		
		window.draw(gameOverText);	// wypisz tekst o koncu gry
		window.draw(pressButtonText);	// wypisz tekst z instrukcja jak zaczac od poczatku
	}
	if (currentGameState == GameState::PAUSED)	// jesli stan gry to PAUSED
	{
		//draw();
		window.draw(pauseBigText);	// wypisz komunikat o zapauzowanej grze
		window.draw(pauseText);	// wypisanie tekstu 

	}
	if (currentGameState == GameState::UNSTARTED)	// jesli stan gry to PAUSED
	{
		window.draw(backgroud);
		window.draw(unstartedBigText);	// wypisz komunikat o zapauzowanej grze
		window.draw(unstartedText);	// wypisanie tekstu 

	}
	window.display();
}

/**
  * \brief Metoda sprawdzajaca pliki z poziomami
  */
void Engine::checkLevelFiles()
{
	ifstream levelsManifest("levels.txt");	// wczytanie pliku levels.txt

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

/**
  * \brief Metoda wczytujaca poziomy
  * param levelNumber numer poziomu jaki ma zostac wczytany
  */
void Engine::loadLevel(int levelNumber)
{
	string levelFile = levels[levelNumber - 1];	// zadeklarowanie zmiennej przechowujacej tablice z poziomami
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

/**
  * \brief Metoda ustawiajaca tekst wyswietlany w grze
  * param textItem deklaracja tekstu
  * param font deklaracja czcionki tekstu
  * param value to wartosc jaka bedzie wyswietlana, czyli sama tresc
  * param color kolor tekstu
  */
void Engine::setupText(Text* textItem, const Font& font, const String& value, int size, Color color)
{
	textItem->setFont(font);	// ustawienie czcionki
	textItem->setString(value);	// ustawienie tresci
	textItem->setCharacterSize(size);	// ustawienie wielkosci napisu
	textItem->setFillColor(color);	// ustawienie koloru napisu

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

/**
  * \brief Metoda zawierajaca glowna petle programu
  */
void Engine::run()
{
	Clock clock;	// deklaracja obiektu zegaru

	while (window.isOpen())	// glowna petla gry
	{
		Time between = clock.restart();

		if(currentGameState == GameState::PAUSED || currentGameState==GameState::GAMEOVER || currentGameState == GameState::UNSTARTED)	// jesli stan gry to GAMEOVER lub PAUSED
		{
			InputControl::input(window, directionQueue,currentGameState,lastGameState, *this);

			if(currentGameState==GameState::GAMEOVER || currentGameState == GameState::UNSTARTED)	// jesli aktualny stan gry to GAMEOVER
			{
				draw();	// to nastepuje wywolanie funkcji draw()
				
			}

			sleep(milliseconds(2));		// uspienie na 2 milisekundy
			continue;

		}

		timeSinceLastMove = timeSinceLastMove + between;

		InputControl::input(window,directionQueue,currentGameState,lastGameState,*this);
		SnakeControl::updateDirection(snakeBody,directionQueue, speed, directionCode, timeSinceLastMove, apple, sectionsToAdd, resolution, currentGameState,walls,
			applesTotal,applesEaten,score, *this);	// funkcja zmieniajaca kierunek poruszania sie weza
		applesText.setString("Apples " + to_string(applesTotal));	// informacja o ilosci wszystkich jablek
		FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
		applesText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

		scoreText.setString("Score " + to_string(score));	// zamiana informacji o wyniku na argumentu typu string
		FloatRect scoreTextBounds = scoreText.getLocalBounds();	// zbadanie rozmiaru napisu
		scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));	// ustawienie pozycji napisu

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