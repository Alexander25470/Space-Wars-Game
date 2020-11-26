#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Game.h"
#include "SelectableItem.h"


class Menu
{
    int width,height;
    float j,k;
    sf::RenderWindow window1;
    sf::Event event;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    SelectableItem quit;
    SelectableItem play;
    SelectableItem options;



public:
    Menu(short int width,short int height, std::string title);
    void gameLoop();
    void eventListener();
    void drawWindow();
};
