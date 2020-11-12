#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <windows.h>
#include "Asteroid.h"
#include <list>
#include "Ship.h"
#include "Bullet.h"



class Game {
    int width,height;
    sf::RenderWindow &window1;
    //sf::CircleShape shape;
    sf::Sprite background;
    sf::Event event;
    //float xCircle,yCircle;
    float frameTime;
    sf::Clock clock;
    sf::Time currentTime;
    float getFrameTime();
    bool gameOver;

    sf::Texture asteroidTexture;
    Animation asteroidAnim;
    sf::Texture bulletTexture;
    Animation bulletAnim;

    std::vector<Entity*> entities;

    Ship *ship;

    sf::Texture shipTexture,shipTexture_M;
    Animation shipAnim,shipAnim_M;



    //aca crear las cosas necesarias para el juego

public:
    Game(short int width,short int height,sf::RenderWindow &_window1);
    void gameLoop();
    void eventListener();
    void drawWindow();
    bool isCollide(Entity *a,Entity *b);

};
