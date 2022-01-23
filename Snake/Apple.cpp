
#include "Apple.h"

#include "SnakeSegment.h"

/*****************************************************************//**
 * \file   AnimatedObject.cpp
 * \brief  Plik zrodlowy klasy zawierajacej metody wirtualne, dziedziczona w celu stworzenia animowanych obiektow w postaci jablek
 *
 * \author Piotr Nowek  Wiktor Mazurczak Bartosz Rozpara
 * \date   November 2021
 ******************************************************************/


 /**
  * \brief Klasa sluzaca do stworzenia stworzenia jablka oraz ustawienia jego parametrow
  */
Apple::Apple()
{
	Vector2f startingPosition(400, 300); // ustawienie parametrow na "mapie"

	sprite.setSize(Vector2f(15, 15));	// ustawienie rozmiaru jablka
	sprite.setFillColor(Color::Magenta);	// wypelnienie kolorem
	sprite.setPosition(startingPosition);	// ustawienie pozycji
}

/**
  * \brief Metoda sluzaca do ustawienia jablka
  */
void Apple::setPosition(Vector2f newPosition)
{
	sprite.setPosition(newPosition);
}

RectangleShape Apple::getSprite()
{
	return sprite;
}

/**
  * \brief Metoda sluzaca do przenoszenia jablka w inne wspolrzedne
  * param apple deklaracja obiektu jablka
  * param snakeBody zadeklarowana po to, aby uzyc do sprawdzenia czy nie zostaly wylosowane wspolrzedne na ktorych znajduje sie cialo
  * param resolution uzywane do obliczenia wielkosci jablka
  * param walls do ustalenia granic
  */
void Apple::moveApple(Apple& apple, vector<SnakeSegment> &snakeBody, Vector2f resolution, vector<Wall>walls)
{
	Vector2f appleResolution = Vector2f(resolution.x / 15 - 2, resolution.y / 15 - 2);	// ustawienie rozdzielczosci jablka
	Vector2f newLocation;
	bool isLocationFine = true;
	srand(time(NULL));
	do
	{
		isLocationFine = true;
		newLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 15;	// losowanie wspolrzednych na ktorych jablko sie pojawi
		newLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 15;

		for (auto& s : snakeBody)
		{
			if (s.getShape().getGlobalBounds().intersects(Rect<float>(newLocation.x, newLocation.y, 20, 20)))	// sprawdzenie czy w tych wspolrzednych moze sie pojawic jablko
			{
				isLocationFine = false;
				break;
			}
		}

		for(auto &w:walls)
		{
			if(w.getShape().getGlobalBounds().intersects(Rect<float>(newLocation.x, newLocation.y, 20, 20)))	// ponowne sprawdzenie wspolrzednych
			{
				isLocationFine = false;
				break;
			}
		}
	} while (!isLocationFine);	// petla ktora trwa dopoki nie zostanma znalezione wspolrzedne w ktorych moze sie pojawic jablko

	apple.setPosition(newLocation);	// ustawienie pozycji jablka
}
