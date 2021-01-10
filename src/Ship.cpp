#include "Ship.h"
#include <iostream>
Ship::Ship()
{
    setName("player");
    _feed = 0;
}

void Ship::advanceShip(bool _move)
{
    if (_move)
    {
        increaseDist(cos(getAngle() * (MATH_PI / 180)) * 0.2, sin(getAngle() * (MATH_PI / 180)) * 0.2);
    }
    else
    {
        setDist(getDistxy().x * 0.975, getDistxy().y * 0.975);
    }

    int maxSpeed = 16;
    float speed = sqrt(getDistxy().x * getDistxy().x + getDistxy().y * getDistxy().y);
    if (speed > maxSpeed)
    {
        increaseDist(maxSpeed / speed, maxSpeed / speed, 2);
    }
}

void Ship::update()
{
    updatePos();
    sf::Vector2f _Pos = getPos();
    if (_Pos.x > width /*width*/)
        setPos(0, _Pos.y);
    if (_Pos.y > height /*height*/)
        setPos(_Pos.x, 0);
    if (_Pos.x < 0)
        setPos(width, _Pos.y);
    if (_Pos.y < 0)
        setPos(_Pos.x, height);
}
bool Ship::isFeeded()
{
    return _feed > 0;
}

void Ship::addFeed(int feed)
{
    _feed+=feed;
}
