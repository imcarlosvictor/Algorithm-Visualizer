#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

// Determines the state of the tile every time it is reset
enum TileState
{
    Start = 0,
    End,
    Wall,
    Path,
    Explored,
    Floor
};

// Add weights to the tile for pathfinding algorithm

class Tile
{
    public:
        Tile(int length, int width, int x_coord, int y_coord);
        void CreateTile();
        void DrawTile(sf::RenderWindow& window);
        void setStartPoint();
        void setEndPoint();
        void setPath();
        void setExplored();
        void setFloor();
        void setWall();
        void setCoordinate(int x, int y);
        long unsigned int getXCoordinate();
        long unsigned int getYCoordinate();
        TileState getTileState();
        int getTileLength();
        int getTileWidth();

    private:
        sf::RectangleShape tile_;
        TileState state_;
        int length_;
        int width_;
        int neighbors[4]; // store the surrounding tiles
        long unsigned int x_position_;
        long unsigned int y_position_;
};