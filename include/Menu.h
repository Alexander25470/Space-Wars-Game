#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include "Game.h"
#include "SelectableText.h"


class Menu
{
    const int vol=5;
    SelectableText backButton;
    sf::Font font;
    int width,height;
    float j,k;
    sf::RenderWindow window1;
    sf::Event event;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Sound shotSound;
    bool fullScreenn;
    void loadConfig();
    std::string language;
    SelectableText playText;
    SelectableText highScoreText;
    SelectableText optionsText;
    SelectableText exitText;
    void gameLoop();
    void eventListener();
    void drawWindow();
    void optionsMenu();
    void highScoreMenu();
    void changeResolution(int&, int&, bool);
    int readHighestScore();

public:
    Menu(/*short int width*/);
    void initializer();

};
