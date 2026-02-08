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
    this->tile_.setFillColor(sf::Color(227,235,238));
    this->tile_.setOutlineColor(sf::Color(73,73,73));
    this->tile_.setOutlineThickness(.5);
    this->tile_.setPosition(this->x_position_, this->y_position_);
}

void Tile::DrawTile(sf::RenderWindow& window)
{
    window.draw(this->tile_);
}

void Tile::setStartPoint()
{
    this->tile_.setFillColor(sf::Color(96,208,254));
    this->state_ = Start;
}

void Tile::setEndPoint()
{
    this->tile_.setFillColor(sf::Color(255,154,48));
    this->state_ = End;
}

void Tile::setPath()
{
    this->tile_.setFillColor(sf::Color(200,254,7));
    this->state_ = Path;
}

void Tile::setExplored()
{
    this->tile_.setFillColor(sf::Color(48,157,122));
    this->state_ = Explored;
}

void Tile::setFloor()
{
    this->tile_.setFillColor(sf::Color(227,235,238));
    this->state_ = Floor;
}

void Tile::setWall()
{
    this->tile_.setFillColor(sf::Color(45,48,53));
    this->state_ = Wall;
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