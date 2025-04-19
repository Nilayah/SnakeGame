#include "Snake.h"

Snake::Snake(int cellSize, Vector2f startPos) : cellSize(cellSize) {
    shape.setSize(Vector2f(cellSize - 2, cellSize - 2));
    shape.setFillColor(Color::Magenta);
    shape.setPosition(startPos);
    direction = Vector2f(cellSize, 0);
}

void Snake::HandleInput() {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        direction = Vector2f(0, -cellSize);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        direction = Vector2f(0, cellSize);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        direction = Vector2f(-cellSize, 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        direction = Vector2f(cellSize, 0);
    }
}

void Snake::Update() {
    shape.move(direction);
}

void Snake::Draw(RenderWindow& window) {
    window.draw(shape);
}
