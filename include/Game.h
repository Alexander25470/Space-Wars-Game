#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <windows.h>
#include "Asteroid.h"
#include <list>
#include "Ship.h"
#include "Bullet.h"
#include "EnemyShip.h"



class Game {
    int width,height;
    unsigned long int time;
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
    sf::Texture enemyBulletTexture;
    Animation enemyBulletAnim;


    std::vector<Entity*> entities;

    Ship *ship;
    EnemyShip *enemyShip;

    sf::Texture shipTexture, shipTexture_M, enemyShipTexture, enemyShipTexture_M;
    Animation shipAnim, shipAnim_M, enemyShipAnim, enemyShipAnim_M;



    //aca crear las cosas necesarias para el juego

public:
    Game(short int width,short int height,sf::RenderWindow &_window1);
    void gameLoop();
    void eventListener();
    void drawWindow();
    bool isCollide(Entity *a,Entity *b);

};
