#include "SnakeControl.h"
#include "Engine.h"
#include "Apple.h"

/**
  * \brief Metoda ktora bezposrednio zmienia kierunek poruszania sie weza
  * param snakeBody uzywane do zmiany kierunku poruszania sie ciala weza
  * param directionQueue do tej kolejki bedzie dodawany nowy kierunek
  * param speed zmienna przechowujaca predkosc porusznaia sie weza
  * param directionCode w tej zmiennej zakodowany jest kierunek
  * param timeSinceLastMove licznik czasu od ostatniej zmiany kierunku
  * param apple uzywane do sprawdzenia czy waz zjadl jablko o raz do powiekszania weza
  * param sectionsToAdd zmienna przechowujaca ilosc mozliwych segmentow weza do dodania do ciala
  * param resolution zmienna przechowujaca rozdzielczosc calego okna
  * param walls przechowuje granice mapy
  * param applesTotal przechowuje ilosc wszystkich jablek ktore sie pojawily
  * param applesEaten przechowuje ilosc jablek ktore waz zjadl podczas rozgrywki
  * param score zmienna przechowujaca wynik
  * param engine niezbedny obiekt klasy engine
  */
void SnakeControl::updateDirection(vector<SnakeSegment> &snakeBody, deque<int> &directionQueue, int speed, int &directionCode, Time &timeSinceLastMove, 
	Apple &apple, int &sectionsToAdd, Vector2f resolution, int &currentGameState,vector<Wall> walls, int &applesTotal, int &applesEaten, unsigned long long& score, Engine& engine)
{
	if(timeSinceLastMove.asSeconds() >= seconds(1.f/ float(speed)).asSeconds())
	{
		Vector2f thisSegmentPositon = snakeBody[0].getPos();	// przypisanie pod pozycje weza aktualna pozycje

		Vector2f lastSegmentPosition = thisSegmentPositon;	// przypisanie pod ostatnia pozycje tej aktualnej

		// sprawdzenie czy nastapila kolizja
		if(!directionQueue.empty())
		{
			switch(directionCode)
			{
			case Direction::UP:
				if(directionQueue.front() != Direction::DOWN)
				{
					directionCode = directionQueue.front();
				}
				break;

			case Direction::DOWN:
				if (directionQueue.front() != Direction::UP)
				{
					directionCode = directionQueue.front();
				}
				break;

			case Direction::RIGHT:
				if (directionQueue.front() != Direction::LEFT)
				{
					directionCode = directionQueue.front();
				}
				break;

			case Direction::LEFT:
				if (directionQueue.front() != Direction::RIGHT)
				{
					directionCode = directionQueue.front();
				}
				break;
			}
			directionQueue.pop_front();
		}

		score = (score + 1) + (applesTotal+1);	// ustawienie informacji wyniku

		if(sectionsToAdd)
		{
			SnakeSegment::addSegment(snakeBody);
			sectionsToAdd--;
		}

		// ustawienie kierunku glowy weza
		switch (directionCode)
		{
		case Direction::RIGHT:
			snakeBody[0].setPos(Vector2f(thisSegmentPositon.x + 20, thisSegmentPositon.y));
			break;

		case Direction::LEFT:
			snakeBody[0].setPos(Vector2f(thisSegmentPositon.x - 20, thisSegmentPositon.y));
			break;

		case Direction::UP:
			snakeBody[0].setPos(Vector2f(thisSegmentPositon.x , thisSegmentPositon.y + 20));
			break;

		case Direction::DOWN:
			snakeBody[0].setPos(Vector2f(thisSegmentPositon.x , thisSegmentPositon.y - 20));
			break;
		}

		// reszta segmentow weza
		for(int i = 1; i<snakeBody.size(); i++)
		{
			thisSegmentPositon = snakeBody[i].getPos();
			snakeBody[i].setPos(lastSegmentPosition);
			lastSegmentPosition = thisSegmentPositon;
		}
		// sprawdzenie czy jablko zostalo zjedzone
		for(auto &s : snakeBody)
		{
			s.updatePos();
			if(snakeBody[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds()))
			{
				applesEaten += 1;
				applesTotal += 1;
				
				bool beginNextLevel = false;
				if(applesEaten >=5)	// jesli zjedzono wiêcej ni¿ 5 jab³ek
				{
					if(engine.currentLevel < engine.maxLexels)	// jesli aktualny poziom nie jest ostatnim
					{
						beginNextLevel = true;
						engine.beginNextLevel();	// rozpocznij kolejny poziom
					}
				}

				if(!beginNextLevel)	// jesli nie ma kolejnych poziomow
				{
					sectionsToAdd += 1;	// przedluz weza
					//if(sectionsToAdd / 4 == 0)
					//{
					speed++;	// zwieksz predkosc weza
					//}
					Apple::moveApple(apple, snakeBody, resolution, walls);
				}
				
			}
		}

		// sprawdzenie czy waz sie ugryzl
		for(int s=1; s<snakeBody.size(); s++)
		{
			if(snakeBody[0].getShape().getGlobalBounds().intersects(snakeBody[s].getShape().getGlobalBounds()))
			{
				currentGameState = GameState::GAMEOVER;	// jesli tak, to zakoncz gre
			}
		}
		// sprawdzenie czy waz uderzyl w sciane
		for(auto &w:walls)
		{
			if(snakeBody[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds()))
			{
				currentGameState = GameState::GAMEOVER;	// jesli tak, to zakoncz gre
			}
		}

		timeSinceLastMove = Time::Zero;	// wyzerowanie licznika czasu od ostatniego ruchu
	}
}
