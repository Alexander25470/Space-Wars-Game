#pragma once
#include <SFML/Graphics.hpp>


class Animation
{
    float frame,speed;
    std::vector<sf::IntRect> frames;

    public:
        sf::Sprite sprite;
        Animation(){};
        Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);
        void update();



};


