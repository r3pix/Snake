#pragma once
#include "Engine.h"

class InputControl
{
public:
	enum  GameState { RUNNING, PAUSED, GAMEOVER };	// zadeklarowanie trzech stanow rozgrywki

	static void input(RenderWindow& window, deque<int>& directionQueue, int& currentGameState, int& lastGameState, Engine &engine);
	static void addDirection(int newDirection, deque<int>& directionQueue);	// funkcja zmieniajaca kierunek poruszania sie
	static void togglePause(int& currentGameState, int& lastGameState);	// funkcja zatrzymujaca rozgrywke

};
