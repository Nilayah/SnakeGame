// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include "Background.h"
#include "Snake.h"

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	int cell_size = 20;

	RenderWindow window(VideoMode(800, 600), "Snake Game"); //window size
	World world(Vector2f(0, 0));

	Background background(800, 600, cell_size, world); //initialize background
	Snake snake(cell_size, Vector2f(400 + cell_size / 2, 300 + cell_size / 2), world); //initialize snake
	snake.HandleCollision(window);

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	Clock moveClock;
	Time moveDelay = milliseconds(150);

	while (true) {
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		snake.HandleInput();

		if (moveClock.getElapsedTime() > moveDelay) { //snake movement clock
			snake.Update();
			moveClock.restart();
		}

		window.clear(Color(0, 0, 0));

		background.Render(window);
		snake.Draw(window);
		
		window.display();
	}

	return 0;
}