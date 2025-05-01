#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include "Fruit.h"

using namespace std;
using namespace sf;
using namespace sfp;

class Snake {
public:
    Snake(Color snakeColor, int score, int cellSize, Vector2f startPos, World& world);
    void Reset(Color color, int& score, int cellSize, Vector2f startPos, World& world);
    void RemoveFromWorld();
    void Update();
    void HandleInput(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right);
    void HandleCollision(RenderWindow& window, Fruit& fruit);
    void HandleSurroundCollision(RenderWindow& window);
    void Grow();
    void Draw(RenderWindow& window);
    PhysicsRectangle& GetHead() { return snakeHead; }
    int GetScore() const { return score; }
    void SetScore(int num);
    bool IsGameOver() const { return gameOver; }

private:
    World& world;
    PhysicsRectangle snakeHead;
    vector<shared_ptr<PhysicsRectangle>> snakeTail;
    Vector2f lastHeadPos;
    int tailLength;
    Vector2f direction;
    int cellSize;
    Color snakeColor;
    bool gameOver;
    int score;
    bool constantGrowth;
};

