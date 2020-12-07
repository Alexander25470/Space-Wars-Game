#pragma once
#include <SFML/Graphics.hpp>


class Animation
{
        float frame,speed;
        std::vector<sf::IntRect> frames;
        sf::Sprite sprite;
    public:
        Animation(){};
        Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);
        void update();
        sf::Sprite &getSprite();
        bool isEnd();



};


