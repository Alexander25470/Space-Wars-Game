#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <windows.h>
#include "Asteroid.h"
#include <list>
class Game {
    int width,height;
    sf::RenderWindow &window1;
    sf::CircleShape shape;
    sf::Sprite background;
    sf::Event event;
    float xCircle,yCircle,frameTime;
    sf::Clock clock;
    sf::Time currentTime;
    float getFrameTime();
    bool gameOver;
    sf::Texture asteroidTexture;
    Animation asteroidAnim;
    std::vector<Asteroid*> asts;
    std::vector<Asteroid*>::iterator astsIterator;

    //aca crear las cosas necesarias para el juego

public:
    Game(short int width,short int height,sf::RenderWindow &_window1);
    void gameLoop();
    void eventListener();
    void drawWindow();

};
