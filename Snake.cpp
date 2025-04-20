#include "Snake.h"

Snake::Snake(Color snakeColor, int cellSize, Vector2f startPos, World& world) : snakeColor(snakeColor), cellSize(cellSize), world(world), gameOver(false), tailLength(0) {
    snakeHead.setSize(Vector2f(cellSize - 2, cellSize - 2));
    snakeHead.setCenter(startPos);
    snakeHead.setFillColor(snakeColor);
    direction = Vector2f(0, cellSize); //go down upon loading
    world.AddPhysicsBody(snakeHead);

    lastHeadPos = startPos;
}

void Snake::HandleInput(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right) {
    if (Keyboard::isKeyPressed(up)) {
        direction = Vector2f(0, -cellSize);
    }
    else if (Keyboard::isKeyPressed(down)) {
        direction = Vector2f(0, cellSize);
    }
    else if (Keyboard::isKeyPressed(left)) {
        direction = Vector2f(-cellSize, 0);
    }
    else if (Keyboard::isKeyPressed(right)) {
        direction = Vector2f(cellSize, 0);
    }
}

void Snake::Update() {
    if (gameOver) return;

    lastHeadPos = snakeHead.getCenter();
    snakeHead.setCenter(snakeHead.getCenter() + direction);

    if (!snakeTail.empty()) {
        Vector2f prevPos = lastHeadPos;
        for (auto& segment : snakeTail) {
            Vector2f currentPos = segment->getCenter();
            segment->setCenter(prevPos);
            prevPos = currentPos;
        }
    }
}

void Snake::HandleCollision(RenderWindow& window, Fruit& fruit) {
    snakeHead.onCollision = [&window, this, &fruit](PhysicsBodyCollisionResult result) {
        if (result.hasCollided) {
            // collison with fruit
            if ((result.object1 == snakeHead && result.object2 == fruit.GetBody()) ||
                (result.object1 == fruit.GetBody() && result.object2 == snakeHead)) {
                Grow();
                fruit.Respawn();
            }
            // collision with the snake's tail or wall (or anything else)
            else {
                gameOver = true;
                std::cout << "Game Over!" << std::endl;
                world.RemovePhysicsBody(snakeHead);
                snakeHead.setFillColor(Color::Transparent);
                snakeHead.setCenter(Vector2f(400 + cellSize / 2, 300 + cellSize / 2));
                window.close();
            }
        }
        };
}

void Snake::Grow() {
    auto newSegment = std::make_shared<PhysicsRectangle>();
    newSegment->setSize(Vector2f(cellSize - 2, cellSize - 2));
    newSegment->setStatic(true);

    Color dimmedColor(
        static_cast<Uint8>(snakeColor.r * 0.6f),
        static_cast<Uint8>(snakeColor.g * 0.6f),
        static_cast<Uint8>(snakeColor.b * 0.6f)
    );
    newSegment->setFillColor(dimmedColor);

    Vector2f newSegmentPos;

    if (snakeTail.empty()) {
        newSegmentPos = lastHeadPos;
    }
    else {
        newSegmentPos = snakeTail.back()->getCenter();
    }

    newSegment->setCenter(newSegmentPos);
    world.AddPhysicsBody(*newSegment);
    snakeTail.push_back(newSegment);
}

void Snake::Draw(RenderWindow& window) {
    window.draw(snakeHead);
    for (auto& segment : snakeTail) {
        window.draw(*segment);
    }
}

PhysicsRectangle& Snake::GetHead() {
    return snakeHead;
}