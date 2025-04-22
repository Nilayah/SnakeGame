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

enum GameState { START, PLAYING, GAME_OVER };
GameState gameState = START;

void InitializeGame(RenderWindow& window, World& world, Background background, Snake& snake1, Snake& snake2, Fruit& fruit, int cellSize, int& score1, int& score2) {
	world = World(Vector2f(0, 0)); // creates a new world

	score1 = snake1.GetScore();
	score2 = snake2.GetScore();

	snake1.Reset(Color::Magenta, score1, cellSize, Vector2f(100 + cellSize / 2, 100 + cellSize / 2), world);
	snake2.Reset(Color::Green, score2, cellSize, Vector2f(680 + cellSize / 2, 100 + cellSize / 2), world);
	fruit.Reset(cellSize, world);

	snake1.HandleCollision(window, fruit);
	snake2.HandleCollision(window, fruit);

	background.AddWallsToWorld(world);
	world.AddPhysicsBody(snake1.GetHead());
	world.AddPhysicsBody(snake2.GetHead());
	world.AddPhysicsBody(fruit.GetBody());
}

int main()
{
	// Fonts and Score
	Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Couldn't load font arial.ttf" << endl;
		exit(1);
	}

	Text startText;
	startText.setFont(font);
	startText.setCharacterSize(36);
	startText.setFillColor(Color::White);
	startText.setString("Press SPACE to Start");
	startText.setPosition(225, 250);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setString("GAME OVER!");
	gameOverText.setPosition(250, 250);
	Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(25);
	restartText.setFillColor(Color::White);
	restartText.setString("Press R to Restart\n  Press Q to Quit");
	restartText.setPosition(300, 305);

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

	// Initialize Game objects
	int cell_size = 20;

	RenderWindow window(VideoMode(800, 600), "Snake Game"); //window size
	World world(Vector2f(0, 0));

	Background background(800, 600, cell_size, world); //initialize background
	Snake snake1(Color::Magenta, score1, cell_size, Vector2f(100 + cell_size / 2, 100 + cell_size / 2), world); //initialize snake 1
	Snake snake2(Color::Green, score2, cell_size, Vector2f(680 + cell_size / 2, 100 + cell_size / 2), world); //initialize snake 2
	Fruit fruit(cell_size, world); //initialize fruit

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	Clock moveClock;
	Time moveDelay = milliseconds(150);

	bool initialized = false;

	while (true) {
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		window.clear(Color(0, 0, 0));
		background.Render(window);

		if (gameState == START) { //START GAME
			window.draw(startText);
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				gameState = PLAYING;
				InitializeGame(window, world, background, snake1, snake2, fruit, cell_size, score1, score2);
				initialized = true;
			}
		}
		else if (gameState == PLAYING) { //PLAYING GAME
			if (!initialized) {
				InitializeGame(window, world, background, snake1, snake2, fruit, cell_size, score1, score2);
				initialized = true;
			}

			snake1.HandleInput(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
			snake2.HandleInput(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);

			if (moveClock.getElapsedTime() > moveDelay) {
				snake1.Update();
				snake2.Update();
				moveClock.restart();
			}

			if (snake1.IsGameOver() || snake2.IsGameOver()) { //detects game over
				gameState = GAME_OVER;
				initialized = false;
			}
		}
		else if (gameState == GAME_OVER) {
			window.draw(gameOverText);
			window.draw(restartText);
			if (Keyboard::isKeyPressed(Keyboard::R)) { // restarts game
				gameState = PLAYING;
				snake1.SetScore(0);
				snake2.SetScore(0);
				InitializeGame(window, world, background, snake1, snake2, fruit, cell_size, score1, score2);
				initialized = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) { // quits game
				window.close();
				return 0;
			}
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