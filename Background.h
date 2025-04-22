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
    void AddWallsToWorld(World& world);
    void Render(RenderWindow& window);

private:
    vector<RectangleShape> tiles;
    vector<RectangleShape> wallShapes;
    PhysicsRectangle top_wall, bottom_wall, left_wall, right_wall;;
    int width;
    int height;
    int cellSize;
    World& world;
};
