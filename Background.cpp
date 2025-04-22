#include "Background.h"

Background::Background(int width, int height, int cellSize, World& world) //walls and checkered background
    : width(width), height(height), cellSize(cellSize), world(world) {

	// Create the Checkered Background
    for (int y = 0; y < height; y += cellSize) {
        for (int x = 0; x < width; x += cellSize) {
            sf::RectangleShape tile(Vector2f(cellSize - 1, cellSize - 1));
            tile.setPosition(static_cast<float>(x), static_cast<float>(y));
            tile.setFillColor(Color(30, 30, 30));
            tiles.push_back(tile);
        }
    }

	float wall_thickness = 40.0f;

	// Create the top wall
	top_wall.setSize(Vector2f(width, wall_thickness));
	top_wall.setCenter(Vector2f(width / 2, 0));
	top_wall.setFillColor(Color(20, 20, 20));
	top_wall.setStatic(true);
	world.AddPhysicsBody(top_wall);

	// Create the bottom wall
	bottom_wall.setSize(Vector2f(width, wall_thickness * 2));
	bottom_wall.setCenter(Vector2f(width / 2, height));
	bottom_wall.setFillColor(Color(20, 20, 20));
	bottom_wall.setStatic(true);
	world.AddPhysicsBody(bottom_wall);

	// Create the left wall
	left_wall.setSize(Vector2f(wall_thickness, height));
	left_wall.setCenter(Vector2f(0, height / 2));
	left_wall.setFillColor(Color(20, 20, 20));
	left_wall.setStatic(true);
	world.AddPhysicsBody(left_wall);

	// Create the right wall
	right_wall.setSize(Vector2f(wall_thickness, height));
	right_wall.setCenter(Vector2f(width, height / 2));
	right_wall.setFillColor(Color(20, 20, 20));
	right_wall.setStatic(true);
	world.AddPhysicsBody(right_wall);
}

void Background::Render(sf::RenderWindow& window) { //draws the walls and background
    for (auto& tile : tiles) {
        window.draw(tile);
    }

	window.draw(top_wall);
	window.draw(bottom_wall);
	window.draw(right_wall);
	window.draw(left_wall);
}
