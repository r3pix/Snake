#include "Wall.h"

/**
  * \brief Metoda ktora ustawia sciany na mapie
  * param position zmienna przechowujaca pozycje scian
  * param size zmienna przechopujaca grubosc scian
  */
Wall::Wall(Vector2f position, Vector2f size)
{
	wallShape.setSize(size);	// ustawienie grubosci sciany
	wallShape.setFillColor(Color::Yellow);	// wypelnienie sciany kolorem zoltym
	wallShape.setPosition(position);	// ustawienie pozycji
}

RectangleShape Wall::getShape()
{
	return wallShape;	// getter ksztaltu scian
}
