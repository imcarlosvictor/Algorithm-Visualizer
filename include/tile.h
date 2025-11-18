#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// Determines the state of the tile every time it is reset
enum TileState
{
    Start = 0,
    End,
    Path,
    Explored,
    Floor,
    Wall
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
        long unsigned int getXCoord();
        long unsigned int getYCoord();
        TileState getTileState();
        int getTileLength();
        int getTileWidth();

    private:
        sf::RectangleShape tile_;
        TileState state_;
        int length_;
        int width_;
        long unsigned int x_coord_;
        long unsigned int y_coord_;
};