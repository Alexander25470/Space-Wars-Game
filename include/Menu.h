#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Game.h"

class Menu
{
    int width,height;
    float j,k;
    sf::RenderWindow window1;
    sf::Event event;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    //sf::Font font;
    sf::Text *text;
public:
    Menu(short int width,short int height, std::string title);
    void gameLoop();
    void eventListener();
    void drawWindow();
};

#endif // MENU_H
