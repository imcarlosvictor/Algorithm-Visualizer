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
    int y_coord = 0;
    // Add tiles
    for (int col = 0; col < 30; col++) 
    {
        int x_coord = 330; // starts at 330 due to the sidebar on the lefthand-side
        for (int row = 0; row < 40; row++) 
        {
            Tile* new_tile = new Tile(length, width, x_coord, y_coord);
            new_tile->CreateTile();
            this->grid_.push_back(new_tile);
            x_coord += 30;
        }
        x_coord = 330;  // Reset x-coordinate
        y_coord += 30;
    }
}

void Grid::ClearGrid() 
{
    for (Tile* tile : this->grid_) {
        tile->setFloor();
    }
}

void Grid::ClearPath() 
{
    std::cout << "hello" << std::endl;
    for (Tile* tile : this->grid_) 
    {
        if (tile->getTileState() == 2 || tile->getTileState() == 3) 
        {
            tile->setFloor();
        }
    }
}

void Grid::RefreshGrid(sf::RenderWindow& window) 
{
    for (Tile* tile : this->grid_) {
        tile->DrawTile(window);
    }
}

// TODO: Both functions work but tiles are only set as wall. setstartpoint() and setendpoint() are being skipped
void Grid::TilePressed(Coordinates coordinate) 
{
    // Find the tile with the coordinates in the vector
    for (Tile* tile : this->grid_) 
    {
        if (tile->getXPosition() == coordinate.x_position && tile->getYPosition() == coordinate.y_position) 
        {
            switch (this->active_tile_state_)
            {
                case CursorAsStartPoint: 
                    tile->setStartPoint();
                    std::cout << "Startpoint" << std::endl;
                    break;
                case CursorAsEndPoint:
                    tile->setEndPoint();
                    std::cout << "Endpoint" << std::endl;
                    break;
                case CursorAsWall:
                    tile->setWall();
                    std::cout << "Wall" << std::endl;
                    break;
            }
        }
        std::cout << "Wall" << std::endl;
        break;
    }
    this->active_tile_state_ = CursorAsWall; // reset tile option
    // std::cout << "********************* " << std::endl;
    std::cout << "active tile state: " << this->active_tile_state_ << std::endl;
}

void Grid::ChangeActiveTile(ActiveTileState user_input)
{
    // Add a check to see if a start/end point is already establish -> return a warning
    if (this->CheckTiles(user_input))
    {
        std::cout << "Tile state has been established" << std::endl;
        this->active_tile_state_ = CursorAsWall;
    } 
    else 
    {
        this->active_tile_state_ = user_input;
        std::cout << "active tile state: " << this->active_tile_state_ << std::endl;
    }
}

bool Grid::CheckTiles(int tile_state)
{
    for (Tile* tile : this->grid_)
    {
        if ( this->active_tile_state_ == tile_state && tile->getTileState() == tile_state)
        {
            std::cout << "Tile state has been established" << std::endl;
            return true;
        }
    }
    return false;
}

void Grid::getTileNeighbors(Coordinates coordinate) 
{
    // Find index of the pressed tile in the vector
    long unsigned int tile_vip_index = 0;
    for (long unsigned int i=0; i<this->grid_.size(); i++) {
        if (this->grid_[i]->getXPosition() == coordinate.x_position && this->grid_[i]->getYPosition() == coordinate.y_position)
            tile_vip_index = i;
    }

    // Get index of neighboring tiles
    // ---------------- [ TOP ] ----------------
    // Top and Bottom neighbors
    if (tile_vip_index >= 40 && tile_vip_index <= 1159) {
        int top_mid_tile_index = tile_vip_index - 40;
        int bottom_mid_tile_index = tile_vip_index + 40;

        /* this->grid_[top_mid_tile_index]->setWall(); */
        /* this->grid_[bottom_mid_tile_index]->setWall(); */

        std::cout << "-----------------------------------------------------" << std::endl;
        std::cout << "Top middle tile: " << this->grid_[top_mid_tile_index]->getTileState() << std::endl;
        std::cout << "Bottom middle tile: " << this->grid_[bottom_mid_tile_index]->getTileState() << std::endl;
    }
    
    // Top neighbors
    if (tile_vip_index < 40) {
        int bottom_mid_tile_index = tile_vip_index + 40;

        /* this->grid_[bottom_mid_tile_index]->setWall(); */

        std::cout << "Bottom middle tile: " << this->grid_[bottom_mid_tile_index]->getTileState() << std::endl;
    }

    // Bottom neighbors
    if (tile_vip_index > 1159) {
        int top_mid_tile_index = tile_vip_index - 40;

        /* this->grid_[top_mid_tile_index]->setWall(); */

        std::cout << "Top middle tile: " << this->grid_[top_mid_tile_index]->getTileState() << std::endl;
    }


    // ---------------- [ RIGHT ] ----------------
    // Right neighbors
    if ((tile_vip_index + 1) % 40 != 0 && tile_vip_index >= 40 && tile_vip_index <= 1159) {
        int top_right_tile_index = tile_vip_index - 39;
        int right_tile_index = tile_vip_index + 1;
        int bottom_right_tile_index = tile_vip_index + 41;

        /* this->grid_[top_right_tile_index]->setWall(); */
        /* this->grid_[right_tile_index]->setWall(); */
        /* this->grid_[bottom_right_tile_index]->setWall(); */

        std::cout << "Top right tile: " << this->grid_[top_right_tile_index]->getTileState() << std::endl;
        std::cout << "Right tile: " << this->grid_[right_tile_index]->getTileState() << std::endl;
        std::cout << "Bottom right tile: " << this->grid_[bottom_right_tile_index]->getTileState() << std::endl;
    }
    
    // Top neighbors
    if (tile_vip_index <= 38) {
        int right_tile_index = tile_vip_index + 1;
        int bottom_right_tile_index = tile_vip_index + 41;

        /* this->grid_[bottom_right_tile_index]->setWall(); */
        /* this->grid_[right_tile_index]->setWall(); */

        std::cout << "Right tile: " << this->grid_[right_tile_index]->getTileState() << std::endl;
        std::cout << "Bottom right tile: " << this->grid_[bottom_right_tile_index]->getTileState() << std::endl;
    }

    // Bottom neighbors
    if (tile_vip_index > 1159 && tile_vip_index != 1199) {
        int right_tile_index = tile_vip_index + 1;
        int top_right_tile_index = tile_vip_index - 39;

        /* this->grid_[right_tile_index]->setWall(); */
        /* this->grid_[top_right_tile_index]->setWall(); */

        std::cout << "Right tile: " << this->grid_[right_tile_index]->getTileState() << std::endl;
        std::cout << "Top right tile: " << this->grid_[top_right_tile_index]->getTileState() << std::endl;
    }


    // ---------------- [ LEFT ] ----------------
    // Left neighbors
    if (tile_vip_index % 40 != 0 && tile_vip_index >= 40 && tile_vip_index <= 1159) {
        int top_left_tile_index = tile_vip_index - 41;
        int left_tile_index = tile_vip_index - 1;
        int bottom_left_tile_index = tile_vip_index + 39;

        /* this->grid_[top_left_tile_index]->setWall(); */
        /* this->grid_[left_tile_index]->setWall(); */
        /* this->grid_[bottom_left_tile_index]->setWall(); */

        std::cout << "Top left tile: " << this->grid_[top_left_tile_index]->getTileState() << std::endl;
        std::cout << "Left tile: " << this->grid_[left_tile_index]->getTileState() << std::endl;
        std::cout << "Bottom left tile: " << this->grid_[bottom_left_tile_index]->getTileState() << std::endl;
    } 

    // Top neighbors
    if (tile_vip_index < 40 && tile_vip_index > 0) {
        int left_tile_index = tile_vip_index - 1;
        int bottom_left_tile_index = tile_vip_index + 39;

        /* this->grid_[left_tile_index]->setWall(); */
        /* this->grid_[bottom_left_tile_index]->setWall(); */

        std::cout << "Left tile: " << this->grid_[left_tile_index]->getTileState() << std::endl;
        std::cout << "Bottom left tile: " << this->grid_[bottom_left_tile_index]->getTileState() << std::endl;
    }

    // Bottom neighbors
    if (tile_vip_index > 1160 && tile_vip_index == 1199) {
        int left_tile_index = tile_vip_index - 1;
        int top_left_tile_index = tile_vip_index - 41;

        /* this->grid_[left_tile_index]->setWall(); */
        /* this->grid_[top_left_tile_index]->setWall(); */

        std::cout << "Left tile: " << this->grid_[left_tile_index]->getTileState() << std::endl;
        std::cout << "Top left tile: " << this->grid_[top_left_tile_index]->getTileState() << std::endl;
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