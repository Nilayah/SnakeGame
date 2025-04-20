#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

class Snake {
public:
    Snake(Color snakeColor, int cellSize, Vector2f startPos, World& world);
    void Update();
    void HandleInput(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right);
    void HandleCollision(RenderWindow& window);
    void Grow();
    void Draw(RenderWindow& window);

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
};

