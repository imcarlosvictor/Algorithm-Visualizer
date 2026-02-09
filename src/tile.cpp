#include "../include/tile.h"

Tile::Tile(int length, int width, int x_position, int y_position)
{
    this->tile_ = sf::RectangleShape(sf::Vector2f(this->length_, this->width_));
    this->state_ = Floor;
    this->length_ = length;
    this->width_ = width;
    this->x_position_ = x_position;
    this->y_position_ = y_position;
}

void Tile::CreateTile()
{
    this->tile_.setSize(sf::Vector2f(this->length_, this->width_));
    // Light theme
    // this->tile_.setFillColor(sf::Color(227,235,238));
    // this->tile_.setOutlineColor(sf::Color(73,73,73));

    // Dark theme
    // this->tile_.setFillColor(sf::Color(45,48,53));
    this->tile_.setFillColor(sf::Color(34,37,38));
    this->tile_.setOutlineColor(sf::Color(10,10,10));

    this->tile_.setOutlineThickness(.5);
    this->tile_.setPosition(this->x_position_, this->y_position_);
}

void Tile::DrawTile(sf::RenderWindow& window)
{
    window.draw(this->tile_);
}

void Tile::setStartPoint()
{
    this->tile_.setFillColor(sf::Color(251,255,108));
    this->state_ = Start;
}

void Tile::setEndPoint()
{
    this->tile_.setFillColor(sf::Color(255,67,38));
    this->state_ = End;
}

void Tile::setPath()
{
    this->tile_.setFillColor(sf::Color(80,99,133));
    this->state_ = Path;
}

void Tile::setExplored()
{
    this->tile_.setFillColor(sf::Color(191,191,191));
    this->state_ = Explored;
}

void Tile::setFloor()
{
    this->tile_.setFillColor(sf::Color(43,48,53));
    this->state_ = Floor;
}

void Tile::setWall()
{
    this->tile_.setFillColor(sf::Color(10,10,10));
    this->state_ = Wall;
    std::cout << "Wall Set" << std::endl;
}

void Tile::setCoordinate(int x, int y)
{
    this->x_position_ = x;
    this->y_position_ = y;
}

long unsigned int Tile::getXCoordinate()
{
    return x_position_;
}

long unsigned int Tile::getYCoordinate()
{
    return y_position_;
}

TileState Tile::getTileState()
{
    return this->state_;
}