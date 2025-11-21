#pragma once
 
#include "./tile.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


struct Coordinates
{
    long unsigned int x;
    long unsigned int y;
};

struct GridDimension
{
    int rows;
    int columns;
};

enum ActiveTileState
{
    CursorAsStartPoint,
    CursorAsEndPoint,
    CursorAsWall,
};

class Grid
{
    public:
        Grid(int rows, int columns);
        void DrawGrid();
        void ClearGrid();
        void ClearPath();
        void RefreshGrid(sf::RenderWindow& window);
        void TilePressed(Coordinates coordinate);
        void ChangeActiveTile(ActiveTileState user_input);
        bool CheckTiles(int tile_state);
        void getTileNeighbors(Coordinates);
        Coordinates getMousePos(sf::Vector2i mouse_pos);
        GridDimension getGridDimension();


    private:
        int rows_;
        int columns_;
        ActiveTileState active_tile_state_ = CursorAsWall;
        std::vector<Tile*> grid_;
};