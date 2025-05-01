#include "Snake.h"

Snake::Snake(Color snakeColor, int score, int cellSize, Vector2f startPos, World& world) : snakeColor(snakeColor), score(score), cellSize(cellSize), world(world), gameOver(false), tailLength(0), constantGrowth(false) {
    snakeHead.setSize(Vector2f(cellSize - 2, cellSize - 2));
    snakeHead.setCenter(startPos);
    snakeHead.setFillColor(snakeColor);
    direction = Vector2f(0, cellSize); //go down upon loading
    world.AddPhysicsBody(snakeHead);

    lastHeadPos = startPos;
}

void Snake::Reset(Color color, int& score, int cellSize, Vector2f startPos, World& world) {
    score = 0;
    tailLength = 0;
    gameOver = false;

    snakeHead.setSize(Vector2f(cellSize - 2, cellSize - 2));
    snakeHead.setCenter(startPos);
    snakeHead.setFillColor(color);
    direction = Vector2f(0, cellSize);

    world.AddPhysicsBody(snakeHead);
    snakeTail.clear();
}

void Snake::RemoveFromWorld() {
    world.RemovePhysicsBody(snakeHead);

    for (auto& segment : snakeTail) {
        world.RemovePhysicsBody(*segment);
    }

    snakeTail.clear();
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

    if (constantGrowth) {
        Grow();
    }

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
    constantGrowth = false;
    snakeHead.onCollision = [&window, this, &fruit](PhysicsBodyCollisionResult result) {
        if (result.hasCollided) {
            // collison with fruit
            if ((result.object1 == snakeHead && result.object2 == fruit.GetBody()) ||
                (result.object1 == fruit.GetBody() && result.object2 == snakeHead)) {
                Grow();
                fruit.Respawn();
                score += 10;
            }
            // collision with the snake's tail or wall (or anything else)
            else {
                gameOver = true;
                //work on head showing itself on the edge wall
            }
        }
        };
}

void Snake::HandleSurroundCollision(RenderWindow& window) {
    constantGrowth = true;
    snakeHead.onCollision = [&window, this](PhysicsBodyCollisionResult result) {
        if (result.hasCollided) {
            gameOver = true;
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

void Snake::SetScore(int num) {
    score = num;
}