#include "SnakeControl.h"
#include "Engine.h"
#include "Apple.h"

void SnakeControl::updateDirection(vector<SnakeSegment> &snakeBody, deque<int> &directionQueue, int speed, int &directionCode, Time &timeSinceLastMove, 
	Apple &apple, int &sectionsToAdd, Vector2f resolution, int &currentGameState,vector<Wall> walls, int &applesTotal, int &applesEaten, unsigned long long& score, Engine& engine)
{
	if(timeSinceLastMove.asSeconds() >= seconds(1.f/ float(speed)).asSeconds())
	{
		Vector2f thisSegmentPositon = snakeBody[0].getPos();

		Vector2f lastSegmentPosition = thisSegmentPositon;

		//collision check
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

		score = (score + 1) + (applesTotal+1);

		if(sectionsToAdd)
		{
			SnakeSegment::addSegment(snakeBody);
			sectionsToAdd--;
		}

		//head
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

		//rest of segments
		for(int i = 1; i<snakeBody.size(); i++)
		{
			thisSegmentPositon = snakeBody[i].getPos();
			snakeBody[i].setPos(lastSegmentPosition);
			lastSegmentPosition = thisSegmentPositon;
		}
		//cheak apple eaten
		for(auto &s : snakeBody)
		{
			s.updatePos();
			if(snakeBody[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds()))
			{
				applesEaten += 1;
				applesTotal += 1;
				
				bool beginNextLevel = false;
				if(applesEaten >=5)
				{
					if(engine.currentLevel < engine.maxLexels)
					{
						beginNextLevel = true;
						engine.beginNextLevel();
					}
				}

				if(!beginNextLevel)
				{
					sectionsToAdd += 1;
					//if(sectionsToAdd / 4 == 0)
					//{
					speed++;
					//}
					Apple::moveApple(apple, snakeBody, resolution, walls);
				}
				
			}
		}

		//check body collision
		for(int s=1; s<snakeBody.size(); s++)
		{
			if(snakeBody[0].getShape().getGlobalBounds().intersects(snakeBody[s].getShape().getGlobalBounds()))
			{
				currentGameState = GameState::GAMEOVER;
			}
		}

		for(auto &w:walls)
		{
			if(snakeBody[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds()))
			{
				currentGameState = GameState::GAMEOVER;
			}
		}

		timeSinceLastMove = Time::Zero;
	}
}
