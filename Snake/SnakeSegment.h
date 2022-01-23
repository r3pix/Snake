#pragma once
#include<sfml/Graphics.hpp>
#include<vector>

using namespace std;


using namespace sf;

class SnakeSegment
{
private:
	Vector2f pos;	// deklaracja zmiennej odpowiedzialnej za pozycje weza
	RectangleShape segment;

public:

	SnakeSegment(Vector2f initPos);
	static void createSnake(vector<SnakeSegment>& snakeBody);	// funkcja tworzaca weza
	static void addSegment(vector<SnakeSegment>& snakeBody);	// funkcja przedluzajaca weza

	Vector2f getPos();	// getter pozycji weza na mapie
	void setPos(Vector2f pos);	// setter pozycji

	RectangleShape getShape();	// funkcja rysujaca weza

	void updatePos();	// funkcja modyfikujaca polozenie weza

	void setColor(Color);	// setter koloru weza
};

