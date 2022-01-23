#include "SnakeControl.h"
#include "InputControl.h"

#include "Engine.h"

using namespace std;

/**
  * \brief Metoda zawierajaca mechanike gry
  * param window zadeklarowana do operacji na oknie gry
  * param directionQueue zadeklarowana do przechowywania informacji na temat wykonanych ruchow przez gracza
  * param currentGameState zmienna przechowujaca aktualny stan gry
  * param lastGameState zmienna przechowujaca poprzedni stan gry (przed aktualnym)
  * param engine deklaracja silnika gry
  */
void InputControl::input(RenderWindow &window,  deque<int>&directionQueue, int &currentGameState, int &lastGameState, Engine &engine)
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
			if (event.key.code == Keyboard::P)
			{
				togglePause(currentGameState, lastGameState);	// jesli nacisnieto odpowiedni przycisk, to zatrzymaj rozgrywke
			}

			if (event.key.code == Keyboard::N)
			{
				currentGameState = GameState::RUNNING;
				lastGameState = GameState::RUNNING;// jesli nacisnieto odpowiedni przycisk, to zatrzymaj rozgrywke
			}

			if(currentGameState == GameState::GAMEOVER)	// jesli aktualny stan gry to GAMEOVER
			{
				if(event.key.code == Keyboard::R)	// jesli nacisnieto przycisk restartujacy gre
				{
					engine.startTheGame();	// uruchom gre ponownie
				}
			}

			if (event.key.code == Keyboard::Escape)	// jesli nacisnieto przycisk Esc
			{
				window.close();	// zamknij gre
			}

			if (event.key.code == Keyboard::S)	// jesli nacisnieto przycisk S
			{
				addDirection(SnakeControl::Direction::UP ,directionQueue);	// zmien kierunek poruszania sie weza
			}

			else if (event.key.code == Keyboard::A)	// jesli nacisnieto przycisk A
			{
				addDirection(SnakeControl::Direction::LEFT, directionQueue);	// zmien kierunek poruszania sie weza
			}

			else if (event.key.code == Keyboard::W)	// jesli nacisnieto przycisk W
			{
				addDirection(SnakeControl::Direction::DOWN, directionQueue);	// zmien kierunek poruszania sie weza
			}

			else if (event.key.code == Keyboard::D)	// jesli nacisnieto przycisk D
			{
				addDirection(SnakeControl::Direction::RIGHT, directionQueue);	// zmien kierunek poruszania sie weza
			}

		}

	}
}

/**
  * \brief Metoda przekazujaca zmiane kierunku
  * param newDirection nowy kierunek poruszania sie weza
  * param directionQueue zadeklarowana do przechowywania informacji na temat wykonanych ruchow przez gracza
  */
void InputControl::addDirection(int newDirection, deque<int> &directionQueue)	// funkcja zmieniajaca kierunek ruchu weza oraz dodajaca kierunek do kolejki
{
	if (directionQueue.empty())	// jesli kolejka jest pusta
	{
		directionQueue.emplace_back(newDirection);	// dodanie nowego kierunku
	}
	else
	{
		if (directionQueue.back() != newDirection)	// jesli poprzedni kierunek rozni sie od obecnego
		{
			directionQueue.emplace_back(newDirection);	// zmien kierunek
		}
	}
}

/**
  * \brief Metoda pauzujaca gre
  * param currentGameState zmienna przechowujaca aktualny stan gry
  * param lastGameState zmienna przechowujaca poprzedni stan gry (przed aktualnym)
  */
void InputControl::togglePause(int& currentGameState, int& lastGameState)	// funkcja pauzujaca rozgrywke
{
	if (currentGameState == GameState::RUNNING)	// jesli stan gry to RUNNING
	{
		lastGameState = currentGameState;	// przypisz obecny stan pod poprzedni stan gry
		currentGameState = GameState::PAUSED;	// pod obecny stan gry przypisz PAUSED
	}
	else if (currentGameState == GameState::PAUSED)	// jesli stan gry to PAUSED
	{
		currentGameState = lastGameState;	// przypisz pod obecny stan poprzedni
	}
}
