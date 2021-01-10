#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include "Asteroid.h"
#include <list>
#include <vector>
#include "Ship.h"
#include "Bullet.h"
#include "EnemyShip.h"
#include <string>
#include <thread>
#include "SelectableText.h"

class Game {
    const int vol=3;
    int asteroidNumber;
    int enemiesNumber;
    int score;
    int bulletCoolDown;
    int width,height;
    int numberOfCosos;
    unsigned long int time;
    float frameTime;
    sf::Font font;
    std::string language, highScoreString;
    std::thread t1;
    sf::Text fpsText;
    std::string fpsString;
    bool updateFps;

    sf::RenderWindow &window1;
    sf::RectangleShape background;
    sf::Event event;

    sf::Clock clock;
    sf::Time currentTime;
    float getFrameTime();
    bool gameOver;


    sf::Sound explosionSound;
    sf::Sound explosionSound2;
    sf::Sound shotSound1;
    sf::Sound shotSound2;

    sf::Text scoreText;

    sf::Texture asteroidTexture;
    Animation asteroidAnim;
    sf::Texture bulletTexture;
    Animation bulletAnim;
    sf::Texture enemyBulletTexture;
    Animation enemyBulletAnim;

    sf::Texture cosoMisteriosoTexture;
    Animation cosoMisteriosoAnim;

    SelectableText resumeButton;
    SelectableText exitButton;

    std::list<Entity*> entities;
    ///std::list<EnemyShip*> enemies;

    Ship *ship;
    EnemyShip *enemyShip;

    sf::Texture shipTexture, shipTexture_M, enemyShipTexture, enemyShipTexture_M, explosionTextureA,explosionTextureB,explosionTextureC;
    Animation shipAnim, shipAnim_M, enemyShipAnim, enemyShipAnim_M, explosionAnimA, explosionAnimB,explosionAnimC ;

    void checkColition(Entity* a);
    void gameLoop();
    void eventListener();
    void drawWindow();
    bool isCollide(Entity *a,Entity *b);
    int readHighestScore();
    void gameOverScreen();///muestra el score y lo guarda si es mayor al maximo
    void saveScore(int);///solo lo guarda si es mayor
    void pauseMenu();
    sf::Vector2i randomGenerator();


    //aca crear las cosas necesarias para el juego

public:
    Game(short int width,short int height,std::string _language,sf::RenderWindow &_window1);

};
