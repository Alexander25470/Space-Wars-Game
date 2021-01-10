#include "Asteroid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Asteroid::Asteroid()
{
    float x = rand() % 16 - 8;
    float y = rand() % 16 - 8;
    while ((int)x == 0)
    {
        x = rand() % 8 - 4;
    }
    while ((int)y == 0)
    {
        y = rand() % 8 - 4;
    }

    setDist(x, y);
    setName("asteroid");
}

void Asteroid::update()
{

    sf::Vector2f _Pos = getPos();

    updatePos();

    if (_Pos.x > width)
        setPos(0, _Pos.y);
    if (_Pos.y > height)
        setPos(_Pos.x, 0);
    if (_Pos.x < 0)
        setPos(width, _Pos.y);
    if (_Pos.y < 0)
        setPos(_Pos.x, height);
}
