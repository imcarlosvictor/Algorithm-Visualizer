#pragma once
 
#include "./tile.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>


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
        void LockStartPoint(Tile* tile, int coordinate_x, int coordinate_y);
        void LockEndPoint(Tile* tile, int coordinate_x, int coordinate_y);
        void ChangeActiveTile(ActiveTileState user_input);
        bool CheckTiles(int tile_state);
        void getTileNeighbors(Coordinates);
        Coordinates getMousePos(sf::Vector2i mouse_pos);
        GridDimension getGridDimension();


    private:
        int rows_;
        int columns_;
        bool start_point_set_ = false;
        bool end_point_set_ = false;
        int start_point_x;
        int start_point_y;
        int end_point_x;
        int end_point_y;
        ActiveTileState active_tile_state_ = CursorAsWall;
        std::vector<Tile*> grid_;
};