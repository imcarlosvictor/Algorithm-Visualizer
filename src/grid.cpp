#include "../include/grid.h"


Grid::Grid(int rows, int columns) 
{
    this->rows_ = rows; 
    this->columns_ = columns;
    this->DrawGrid();
}

void Grid::DrawGrid() 
{
    int length = 30, width = 30;
    int y_coordinate = 0;
    // Add tiles
    for (int col = 0; col < this->columns_; col++) 
    {
        int x_coordinate = 330; // starts at 330 due to the sidebar on the lefthand-side
        for (int row = 0; row < this->rows_; row++) 
        {
            Tile* new_tile = new Tile(length, width, x_coordinate, y_coordinate);
            new_tile->SetTileCharacteristics();
            this->grid_.push_back(new_tile);
            x_coordinate += 30;
        }
        x_coordinate = 330;  // Reset x-coordinate
        y_coordinate += 30;
    }
}

/*
    Updates the grid every time a tile is changed by the user. 
    This is called in the main event loop in window.cpp
*/
void Grid::RefreshGrid(sf::RenderWindow& window) 
{
    for (Tile* tile : this->grid_) 
    {
        tile->DrawTile(window);
    }
}

/*
    Clears the grid of all tiles and resets the start/end point lock. 
    This is called when the user clicks on the "Clear Maze" button in the sidebar.
*/
void Grid::ClearGrid() 
{
    for (Tile* tile : this->grid_) 
    {
        tile->setFloor();
    }
    this->start_point_set_ = false;
    this->end_point_set_ = false;
}

void Grid::ClearPath() 
{
    for (Tile* tile : this->grid_) 
    {
        if (tile->getTileState() == 2 || tile->getTileState() == 3) 
        {
            tile->setFloor();
        }
    }
}

void Grid::TilePressed(Coordinates cursor_coordinate) 
{
    // Find the tile with the coordinates in the vector
    for (Tile* tile : this->grid_) 
    {
        if (tile->getXCoordinate() == cursor_coordinate.x && tile->getYCoordinate() == cursor_coordinate.y) 
        {
            switch (this->active_tile_state_)
            {
                case CursorAsStartPoint: 
                    if (this->start_point_set_) 
                    {
                        break;
                    } 
                    else 
                    {
                        tile->setStartPoint();
                        this->start_point_set_ = true;
                        this->start_point_x = tile->getXCoordinate();
                        this->start_point_y = tile->getYCoordinate();
                        this->getTileNeighbors(cursor_coordinate);
                        std::cout << this->grid_.size() << std::endl;
                        break;
                    }
                case CursorAsEndPoint:
                    if (this->end_point_set_) 
                    {
                        break;
                    } 
                    else 
                    {
                        tile->setEndPoint();
                        this->end_point_set_ = true;
                        this->end_point_x = tile->getXCoordinate();
                        this->end_point_y = tile->getYCoordinate();
                        this->getTileNeighbors(cursor_coordinate);
                        break;
                    }
                    break;
                case CursorAsWall:
                    tile->setWall();
                    // Call both functions to maintain the start/end points if they have been set by the user
                    LockStartPoint(tile, cursor_coordinate.x, cursor_coordinate.y);
                    LockEndPoint(tile, cursor_coordinate.x, cursor_coordinate.y);
                    break;
            }
        }
    }
}

/*
    Locks the END point in place so that it cannot be overridden by the user when they click on the "Wall" button. 
    This is called in the TilePressed function.
*/
void Grid::LockStartPoint(Tile* tile, int coordinate_x, int coordinate_y)
{
    if (coordinate_x == this->start_point_x && coordinate_y == this->start_point_y)
    {
        tile->setStartPoint();
    }
}

/*
    Locks the START point in place so that it cannot be overridden by the user when they click on the "Wall" button. 
    This is called in the TilePressed function.
*/
void Grid::LockEndPoint(Tile* tile, int coordinate_x, int coordinate_y)
{
    if (coordinate_x == this->end_point_x && coordinate_y == this->end_point_y)
    {
        tile->setEndPoint();
    }
}

/*
    The active tile state is updated when the user clicks on either the start/end/wall buttons
*/
void Grid::ChangeActiveTile(ActiveTileState user_input)
{
    this->active_tile_state_ = user_input;
}

/*
    Gets the neighboring tiles of a tile that the user clicks on. This is used for the maze generation algorithms. 
    This is called in the TilePressed function.
*/
void Grid::getTileNeighbors(Coordinates coordinate) 
{
    // Find index of the pressed tile in the vector
    long unsigned int tile_vip_index = 0;
    for (long unsigned int i = 0; i < this->grid_.size(); i++) {
        if (this->grid_[i]->getXCoordinate() == coordinate.x && this->grid_[i]->getYCoordinate() == coordinate.y)
            tile_vip_index = i;
    }

    // Get index of neighboring tiles
    // ----------------------------------------------- [ TOP ] -----------------------------------------------
    // TOP & BOTTOM TILE if i is within the grid 
    if (tile_vip_index >= 40 && tile_vip_index <= 1159) {
        int top_mid_tile_index = tile_vip_index - 40;
        int bottom_mid_tile_index = tile_vip_index + 40;

        this->grid_[top_mid_tile_index]->setWall();
        this->grid_[bottom_mid_tile_index]->setWall();

        std::cout << "-----------------------------------------------------" << std::endl;
        std::cout << "Top middle tile: " << this->grid_[top_mid_tile_index]->getTileState() << std::endl;
        std::cout << "Bottom middle tile: " << this->grid_[bottom_mid_tile_index]->getTileState() << std::endl;
    }
    
    // TOP OF GRID 
    if (tile_vip_index < 40) {
        int bottom_mid_tile_index = tile_vip_index + 40;

        this->grid_[bottom_mid_tile_index]->setWall(); 

        std::cout << "Bottom middle tile: " << this->grid_[bottom_mid_tile_index]->getTileState() << std::endl;
    }

    // BOTTOM OF GRID 
    if (tile_vip_index > 1159) {
        int top_mid_tile_index = tile_vip_index - 40;

        this->grid_[top_mid_tile_index]->setWall();

        std::cout << "Top middle tile: " << this->grid_[top_mid_tile_index]->getTileState() << std::endl;
    }


    // ----------------------------------------------- [ RIGHT ] -----------------------------------------------
    // RIGHT TILE if [i] is within the grid 
    if ((tile_vip_index + 1) % 40 != 0 && tile_vip_index >= 40 && tile_vip_index <= 1159) {
        int right_tile_index = tile_vip_index + 1;
        // int top_right_tile_index = tile_vip_index - 39;
        // int bottom_right_tile_index = tile_vip_index + 41;

        this->grid_[right_tile_index]->setWall();
        /* this->grid_[top_right_tile_index]->setWall(); */
        /* this->grid_[bottom_right_tile_index]->setWall(); */

        std::cout << "Right tile: " << this->grid_[right_tile_index]->getTileState() << std::endl;
        // std::cout << "Top right tile: " << this->grid_[top_right_tile_index]->getTileState() << std::endl;
        // std::cout << "Bottom right tile: " << this->grid_[bottom_right_tile_index]->getTileState() << std::endl;
    }
    
    // TOP OF GRID 
    if (tile_vip_index <= 38) {
        int right_tile_index = tile_vip_index + 1;
        // int bottom_right_tile_index = tile_vip_index + 41;

         this->grid_[right_tile_index]->setWall();
        /* this->grid_[bottom_right_tile_index]->setWall(); */

        std::cout << "Right tile: " << this->grid_[right_tile_index]->getTileState() << std::endl;
        // std::cout << "Bottom right tile: " << this->grid_[bottom_right_tile_index]->getTileState() << std::endl;
    }

    // BOTTOM OF GRID 
    if (tile_vip_index > 1159 && tile_vip_index != 1199) {
        int right_tile_index = tile_vip_index + 1;
        // int top_right_tile_index = tile_vip_index - 39;

        this->grid_[right_tile_index]->setWall();
        /* this->grid_[top_right_tile_index]->setWall(); */

        std::cout << "Right tile: " << this->grid_[right_tile_index]->getTileState() << std::endl;
        // std::cout << "Top right tile: " << this->grid_[top_right_tile_index]->getTileState() << std::endl;
    }


    // ----------------------------------------------- [ LEFT ] -----------------------------------------------
    // Left neighbors
    if (tile_vip_index % 40 != 0 && tile_vip_index >= 40 && tile_vip_index <= 1159) {
        int left_tile_index = tile_vip_index - 1;
        // int top_left_tile_index = tile_vip_index - 41;
        // int bottom_left_tile_index = tile_vip_index + 39;

        this->grid_[left_tile_index]->setWall();
        /* this->grid_[top_left_tile_index]->setWall(); */
        /* this->grid_[bottom_left_tile_index]->setWall(); */

        std::cout << "Left tile: " << this->grid_[left_tile_index]->getTileState() << std::endl;
        // std::cout << "Top left tile: " << this->grid_[top_left_tile_index]->getTileState() << std::endl;
        // std::cout << "Bottom left tile: " << this->grid_[bottom_left_tile_index]->getTileState() << std::endl;
    } 

    // TOP OF GRID 
    if (tile_vip_index < 40 && tile_vip_index > 0) {
        int left_tile_index = tile_vip_index - 1;
        // int bottom_left_tile_index = tile_vip_index + 39;

        this->grid_[left_tile_index]->setWall();
        /* this->grid_[bottom_left_tile_index]->setWall(); */

        std::cout << "Left tile: " << this->grid_[left_tile_index]->getTileState() << std::endl;
        // std::cout << "Bottom left tile: " << this->grid_[bottom_left_tile_index]->getTileState() << std::endl;
    }

    // BOTTOM OF GRID 
    if (tile_vip_index > 1160 && tile_vip_index == 1199) {
        int left_tile_index = tile_vip_index - 1;
        // int top_left_tile_index = tile_vip_index - 41;

        this->grid_[left_tile_index]->setWall();
        /* this->grid_[top_left_tile_index]->setWall(); */

        std::cout << "Left tile: " << this->grid_[left_tile_index]->getTileState() << std::endl;
        // std::cout << "Top left tile: " << this->grid_[top_left_tile_index]->getTileState() << std::endl;
    }
}

/*
 * Contains the logic for generating maze algorithms depending on user choice
 */
/* void Grid::GenerateMazeAlgorithms(Grid* grid_ptr, MazeAlgorithms* maze_algo_ptr_, const int algo_index) { */
/*     switch (algo_index) { */
/*         case 0: */
/*             /1* maze_algo_ptr_->RecursiveDivision(grid_ptr, grid_dim.rows, grid_dim.columns); *1/ */
/*             maze_algo_ptr_->RecursiveDivision(grid_ptr, grid_ptr->getGridDimension().rows, grid_ptr->getGridDimension().columns); */
/*             break; */
/*         case 1: */
/*             std::cout << 11 << std::endl; */
/*             break; */
/*         case 2: */
/*             std::cout << 22 << std::endl; */
/*             break; */
/*     } */
/* } */

Coordinates Grid::getMousePos(sf::Vector2i mouse_pos) 
{
    // Find the coordinate of the tile (Top left of tile)
    long unsigned int x = (mouse_pos.x / 30) * 30;
    long unsigned int y = (mouse_pos.y - (mouse_pos.y % 30));
    Coordinates position {x, y};
    return position;
}

GridDimension Grid::getGridDimension() 
{
    int rows = this->rows_;
    int columns = this->columns_;
    GridDimension grid_dim {rows, columns};
    return grid_dim;
}