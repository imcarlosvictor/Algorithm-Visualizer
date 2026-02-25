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

void Tile::SetTileCharacteristics()
{
    this->tile_.setSize(sf::Vector2f(this->length_, this->width_));
    this->tile_.setFillColor(sf::Color(10,10,10));
    this->tile_.setOutlineColor(sf::Color(17,17,17));
    this->tile_.setOutlineThickness(.5);
    this->tile_.setPosition(this->x_position_, this->y_position_);
}

void Tile::DrawTile(sf::RenderWindow& window)
{
    window.draw(this->tile_);
}

void Tile::setStartPoint()
{
    this->tile_.setFillColor(sf::Color(158,248,10));
    this->state_ = Start;
}

void Tile::setEndPoint()
{
    this->tile_.setFillColor(sf::Color(255,67,38));
    this->state_ = End;
}

void Tile::setPath()
{
    this->tile_.setFillColor(sf::Color(254,224,0));
    this->state_ = Path;
}

void Tile::setExplored()
{
    this->tile_.setFillColor(sf::Color(20,122,247));
    this->state_ = Explored;
}

void Tile::setFloor()
{
    // this->tile_.setFillColor(sf::Color(43,48,53)); // blue-grey floor
    // this->tile_.setFillColor(sf::Color(34,37,38));
    this->tile_.setFillColor(sf::Color(10,10,10));
    this->state_ = Floor;
}

void Tile::setWall()
{
    // this->tile_.setFillColor(sf::Color(10,10,10));
    // this->tile_.setFillColor(sf::Color(34,37,38));
    this->tile_.setFillColor(sf::Color(68,66,68));
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