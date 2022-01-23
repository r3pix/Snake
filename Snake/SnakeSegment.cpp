#include "SnakeSegment.h"

using namespace std;

/**
  * \brief Metoda ktora ustawia parametry poczatkowe weza
  * param initPos poczatkowe umiejscowienie weza
  */
SnakeSegment::SnakeSegment(Vector2f initPos)
{
	segment.setSize(Vector2f(15, 15));	// ustawienei rozmiaru weza
	segment.setFillColor(Color::Cyan);	// wypelnienie weza kolorem
	segment.setPosition(initPos);	// ustawienie go w pozycji poczatkowej
	pos = initPos;	// przypisanie pod aktualna pozycje pozycji poczatkowej
}

/**
  * \brief Metoda ktora zwraca pozycje weza
  */
Vector2f SnakeSegment::getPos()
{
	return pos;
}

/**
  * \brief Metoda ktora ustawia pozycje weza
  */
void SnakeSegment::setPos(Vector2f pos)
{
	this->pos = pos;
}

/**
  * \brief Metoda ktora zwraca ksztaltu weza
  */
RectangleShape SnakeSegment::getShape()
{
	return segment;
}

/**
  * \brief Metoda ktora uaktualnia pozycje weza
  */
void SnakeSegment::updatePos()
{
	segment.setPosition(pos);
}

/**
  * \brief Metoda ktora ustawia kolor weza
  */
void SnakeSegment::setColor(Color color)
{
	segment.setFillColor(color);
}

/**
  * \brief Metoda ktora tworzy weza
  * param snakeBody zadeklarowanie obiektu weza
  */
void SnakeSegment::createSnake(vector<SnakeSegment> &snakeBody)
{
	snakeBody.clear();	// wyczyszczenie informacji o wezu
	snakeBody.emplace_back(Vector2f(100, 100));
	snakeBody[0].setColor(Color::Red);	// ustawienie koloru weza
	snakeBody.emplace_back(Vector2f(80, 100));
	snakeBody.emplace_back(Vector2f(60, 100));
}

/**
  * \brief Metoda ktora przedluza cialo weza
  * param snakeBody potrzebna do operacji na ciele weza (przedluzeniu go)
  */
void SnakeSegment::addSegment(vector<SnakeSegment>& snakeBody)
{
	Vector2f newPos = snakeBody[snakeBody.size() - 1].getPos();	// utworzenie nowego ciala weza
	snakeBody.emplace_back(Vector2f(newPos));	// zamiana starego weza na nowego, z dluzszym cialem
}