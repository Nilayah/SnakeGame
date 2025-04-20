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
	Snake snake1(Color::Magenta, cell_size, Vector2f(700 + cell_size / 2, 100 + cell_size / 2), world); //initialize snake 1
	Snake snake2(Color::Green, cell_size, Vector2f(100 + cell_size / 2, 100 + cell_size / 2), world); //initialize snake 2
	snake1.HandleCollision(window);
	snake2.HandleCollision(window);

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

		snake1.HandleInput(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);
		snake2.HandleInput(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);

		if (moveClock.getElapsedTime() > moveDelay) { //snake movement clock
			snake1.Update();
			snake1.Grow(); //TESTING GROW IS WORKING
			snake2.Update();
			snake2.Grow(); //TESTING GROW IS WORKING
			moveClock.restart();
		}
		
		window.clear(Color(0, 0, 0));

		background.Render(window);
		snake1.Draw(window);
		snake2.Draw(window);
		
		window.display();
	}

	return 0;
}