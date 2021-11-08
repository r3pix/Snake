#pragma once
#include<sfml/Graphics.hpp>
#include<vector>

using namespace std;


using namespace sf;

class SnakeSegment
{
private:
	Vector2f pos;
	RectangleShape segment;

public:

	SnakeSegment(Vector2f initPos);
	static void createSnake(vector<SnakeSegment>& snakeBody);
	static void addSegment(vector<SnakeSegment>& snakeBody);

	Vector2f getPos();
	void setPos(Vector2f pos);

	RectangleShape getShape();

	void updatePos();

	void setColor(Color);
};

