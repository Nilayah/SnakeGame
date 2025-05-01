#include "Fruit.h"
#include <cstdlib>

Fruit::Fruit(int cellSize, World& world) : cellSize(cellSize), world(world) {
    body.setSize(Vector2f(cellSize - 4, cellSize - 4));
    body.setFillColor(Color::Red);
    body.setStatic(true);
    world.AddPhysicsBody(body);
    Respawn();
}

void Fruit::Reset(int cellSize, World& world) {
    body.setSize(Vector2f(cellSize - 4, cellSize - 4));
    body.setFillColor(Color::Red);
    body.setStatic(true);
    Respawn();
}

void Fruit::RemoveFromWorld() {
    world.RemovePhysicsBody(body);
}

void Fruit::Respawn() {
    // work on having a random fruit everytime game is played
    int cols = 800 / cellSize;
    int rows = 600 / cellSize;

    int x = rand() % cols;
    int y = rand() % rows;

    body.setCenter(Vector2f(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2));
}

void Fruit::Draw(RenderWindow& window) {
    window.draw(body);
}

PhysicsRectangle& Fruit::GetBody() {
    return body;
}
