#pragma once
#include <SFPhysics.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace sfp;

class Fruit {
public:
    Fruit(int cellSize, World& world);
    void Respawn();
    void Draw(RenderWindow& window);
    PhysicsRectangle& GetBody();

private:
    PhysicsRectangle body;
    int cellSize;
    World& world;
};