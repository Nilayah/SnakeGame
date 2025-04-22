// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include "Background.h"
#include "Snake.h"
#include "Fruit.h"

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Fonts and Score
	Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Couldn't load font arial.ttf" << endl;
		exit(1);
	}
	bool gameOver = false;
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setString("GAME OVER!");
	gameOverText.setPosition(250, 250);

	int score1 = 0;
	int score2 = 0;
	Text scoreText1;
	scoreText1.setFont(font);
	scoreText1.setCharacterSize(24);
	scoreText1.setFillColor(Color::Magenta);
	scoreText1.setPosition(100, 565);
	Text scoreText2;
	scoreText2.setFont(font);
	scoreText2.setCharacterSize(24);
	scoreText2.setFillColor(Color::Green);
	scoreText2.setPosition(680, 565);

	// Initialize Game
	int cell_size = 20;

	RenderWindow window(VideoMode(800, 600), "Snake Game"); //window size
	World world(Vector2f(0, 0));

	Background background(800, 600, cell_size, world); //initialize background
	Snake snake1(Color::Magenta, score1, cell_size, Vector2f(100 + cell_size / 2, 100 + cell_size / 2), world); //initialize snake 1
	Snake snake2(Color::Green, score2, cell_size, Vector2f(680 + cell_size / 2, 100 + cell_size / 2), world); //initialize snake 2
	Fruit fruit(cell_size, world); //initialize fruit

	snake1.HandleCollision(window, fruit);
	snake2.HandleCollision(window, fruit);

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

		snake1.HandleInput(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
		snake2.HandleInput(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);

		if (!gameOver && moveClock.getElapsedTime() > moveDelay) { //snake movement clock
			snake1.Update();
			snake2.Update();
			moveClock.restart();
		}

		window.clear(Color(0, 0, 0));

		background.Render(window);

		if (snake1.IsGameOver() || snake2.IsGameOver()) { //detects game over
			gameOver = true;

			world.RemovePhysicsBody(snake1.GetHead());
			world.RemovePhysicsBody(snake2.GetHead());

			window.draw(gameOverText);
		}

		scoreText1.setString(to_string(snake1.GetScore()));
		scoreText2.setString(to_string(snake2.GetScore()));

		window.draw(scoreText1);
		window.draw(scoreText2);

		snake1.Draw(window);
		snake2.Draw(window);
		fruit.Draw(window);
		
		window.display();
	}

	return 0;
}