#include "Snake.h"

Snake::Snake(int cellSize, Vector2f startPos, World& world) : cellSize(cellSize), world(world), gameOver(false) {
    snakeHead.setSize(Vector2f(cellSize - 2, cellSize - 2));
    snakeHead.setCenter(startPos);
    snakeHead.setFillColor(Color::Magenta);
    direction = Vector2f(0, 0);
    world.AddPhysicsBody(snakeHead);
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
    if (gameOver) {
        return;
    }

    snakeHead.setCenter(snakeHead.getCenter() + direction);
}

void Snake::HandleCollision(RenderWindow& window) {
    snakeHead.onCollision = [&window, this](PhysicsBodyCollisionResult result) {
        gameOver = true;
        std::cout << "Game Over!" << std::endl;
        snakeHead.setFillColor(Color::Transparent);
        snakeHead.setCenter(Vector2f(400 + cellSize / 2, 300 + cellSize / 2));
        window.close();
        //work on the snake not showing up on the border when game is over
    };
}

void Snake::Draw(RenderWindow& window) {
    window.draw(snakeHead);
}
