#pragma once
#include <SFML/Graphics.hpp>


class Animation:public sf::Sprite
{
        float frame,speed;
        std::vector<sf::IntRect> frames;
    public:
        Animation(){};
        Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);
        void update();
        bool isEnd();



};


