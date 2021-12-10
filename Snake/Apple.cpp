
#include "Apple.h"

#include "SnakeSegment.h"

Apple::Apple()
{
	Vector2f startingPosition(400, 300);

	sprite.setSize(Vector2f(15, 15));
	sprite.setFillColor(Color::Magenta);
	sprite.setPosition(startingPosition);
}

void Apple::setPosition(Vector2f newPosition)
{
	sprite.setPosition(newPosition);
}

RectangleShape Apple::getSprite()
{
	return sprite;
}

void Apple::moveApple(Apple& apple, vector<SnakeSegment> &snakeBody, Vector2f resolution)
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

		for (auto& s : snakeBody)
		{
			if (s.getShape().getGlobalBounds().intersects(Rect<float>(newLocation.x, newLocation.y, 20, 20)))
			{
				isLocationFine = false;
				break;
			}

		}
	} while (!isLocationFine);

	apple.setPosition(newLocation);
}
