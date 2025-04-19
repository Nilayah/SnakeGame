#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

class Snake {
public:
    Snake(int cellSize, Vector2f startPos, World& world);
    void Update();
    void HandleInput();
    void HandleCollision(RenderWindow& window);
    void Draw(RenderWindow& window);

private:
    World& world;
    PhysicsRectangle snakeHead;
    Vector2f direction;
    int cellSize;
    bool gameOver;
};

