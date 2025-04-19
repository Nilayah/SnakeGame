#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Snake {
public:
    Snake(int cellSize, Vector2f startPos);
    void Update();
    void HandleInput();
    void Draw(RenderWindow& window);

private:
    RectangleShape shape;
    Vector2f direction;
    int cellSize;
};

