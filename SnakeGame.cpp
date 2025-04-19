// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include "Background.h"

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Snake Game"); //window size
	World world(Vector2f(0, 1)); //gravity

	Background background(800, 600, 20, world); //initialize background

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	while (true) {
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			lastTime = currentTime;
		}

		window.clear(Color(0, 0, 0));

		background.Render(window);

		window.display();
	}

	return 0;
}