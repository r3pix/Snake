#include "Engine.h"


const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine()
{
	resolution = Vector2f(800, 600);
	window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
	window.setFramerateLimit(fps);
	backgroud.setSize(Vector2f(800, 600));
	backgroud.setFillColor(Color(169,169,169));

	speed = 3;

	directionCode = Direction::RIGHT;
	timeSinceLastMove = Time::Zero;

	createSnake();
}

void Engine::draw()
{
	window.clear();
	window.draw(backgroud);
	//window.clear(Color::Black);

	for(auto &s: snakeBody)
	{
		window.draw(s.getShape());
	}

	window.display();
}



void Engine::run()
{
	Clock clock;

	while (window.isOpen())
	{
		Time between = clock.restart();
		timeSinceLastMove = timeSinceLastMove + between;

		input();
		updateDirection();
		draw();
	}
}
