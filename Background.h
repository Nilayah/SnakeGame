#pragma once
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>

using namespace std;
using namespace sf;
using namespace sfp;

class Background {
public:
    Background(int width, int height, int cellSize, World& world);
    void Render(RenderWindow& window);

private:
    vector<RectangleShape> tiles;
    vector<RectangleShape> wallShapes;
    vector<PhysicsRectangle> walls;
    int width;
    int height;
    int cellSize;
    World& world;
};
