#include "Game.h"

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

Game::Game(short int _width, short int _height, std::string _language, sf::RenderWindow &_window1) : window1(_window1)
{
    language = _language;
    score = 0;
    enemiesNumber = 0;
    asteroidNumber = 0;
    time = 0;
    numberOfCosos = 0;
    bulletCoolDown = 0;
    gameOver = false;
    ///window1=_window1;
    width = _width;
    height = _height;
    updateFps = false;

    ///aca inicializar las cosas
    window1.setFramerateLimit(60);
    ///cargo imagen de fondo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images\\background.jpg");
    background.setTexture(&backgroundTexture);
    background.setSize(sf::Vector2f(width, height));
    ///termina de cargar la imagen de fondo

    /// cargando sonidos
    ///explosion
    sf::SoundBuffer explosionSoundBuffer;
    explosionSoundBuffer.loadFromFile("sounds\\spinner-osu.wav");
    explosionSound.setBuffer(explosionSoundBuffer);
    explosionSound.setVolume(vol);

    ///explosion2
    sf::SoundBuffer explosionSound2Buffer;
    explosionSound2Buffer.loadFromFile("sounds\\drum-hitfinish.wav");
    explosionSound2.setBuffer(explosionSound2Buffer);
    explosionSound2.setVolume(vol);

    ///disparo 1
    sf::SoundBuffer shotSound1Buffer;
    shotSound1Buffer.loadFromFile("sounds\\soft-hitclap.wav");
    shotSound1.setBuffer(shotSound1Buffer);
    shotSound1.setVolume(vol - 1);

    ///disparo 2
    sf::SoundBuffer shotSound2Buffer;
    shotSound2Buffer.loadFromFile("sounds\\drum-hitnormal.wav");
    shotSound2.setBuffer(shotSound2Buffer);
    shotSound2.setVolume(vol - 1);

    ///sonidos cargados

    asteroidTexture.loadFromFile("images/rock.png");
    asteroidAnim = Animation(asteroidTexture, 0, 0, 64, 64, 16, 0.2);

    bulletTexture.loadFromFile("images/fire_blue.png");
    bulletAnim = Animation(bulletTexture, 0, 0, 32, 64, 16, 0.8);

    enemyBulletTexture.loadFromFile("images/fire_red.png");
    enemyBulletAnim = Animation(enemyBulletTexture, 0, 0, 32, 64, 16, 0.8);

    ///sf::Font font;
    font.loadFromFile("fonts/PressStart2P-Regular.ttf");

    scoreText.setFont(font);
    highScoreString = language.compare("en") == 0 ? "Score: " : "Puntos: ";
    scoreText.setString(highScoreString);
    scoreText.setColor(sf::Color(0, 255, 0));
    scoreText.setPosition(0, 0);

    fpsText.setFont(font);
    fpsText.setString("fps: ");
    fpsText.setColor(sf::Color(0, 255, 0));
    fpsText.setPosition(width - 300, 0);

    ///-----------------------------------------------------------------------------------------
    ///---------------------EXPLOSIONES---------------------------------------------------------
    ///-----------------------------------------------------------------------------------------
    explosionTextureA.loadFromFile("images\\explosions\\type_A.png");
    explosionTextureB.loadFromFile("images\\explosions\\type_B.png");
    explosionTextureC.loadFromFile("images\\explosions\\type_C.png");

    explosionAnimA = Animation(explosionTextureA, 0, 0, 50, 50, 48, 0.5); ///esta es para las balas
    explosionAnimB = Animation(explosionTextureB, 0, 0, 192, 192, 64, 0.5);
    explosionAnimC = Animation(explosionTextureC, 0, 0, 256, 256, 48, 0.5);

    ///-----------------------------------------------------------------------------------------
    ///-----------------------------------------------------------------------------------------
    ///-----------------------------------------------------------------------------------------

    cosoMisteriosoTexture.loadFromFile("images\\coso.png");
    cosoMisteriosoAnim = Animation(cosoMisteriosoTexture, 0, 0, 50, 50, 1, 0);

    /*for(int i=0;i<1;i++)
    {
        asteroidNumber++;
        Asteroid *a = new Asteroid();
        a->initializer(width,height,asteroidAnim, (rand()%width)+width, (rand()%height)+height, rand()%360, 25);
        entities.push_back(a);
    }*/

    shipTexture.loadFromFile("images/ship01.png");
    shipTexture_M.loadFromFile("images/ship01.png");
    shipAnim = Animation(shipTexture, 38, 0, 40, 52, 1, 0);
    shipAnim_M = Animation(shipTexture_M, 38, 53, 40, 52, 1, 0);

    enemyShipTexture.loadFromFile("images/ship04.png");
    enemyShipTexture_M.loadFromFile("images/ship04.png");
    enemyShipAnim = Animation(enemyShipTexture, 40, 0, 40, 40, 1, 0);
    enemyShipAnim_M = Animation(enemyShipTexture_M, 39, 57, 39, 46, 1, 0);

    ship = new Ship();
    ship->initializer(width, height, shipAnim, (width / 2), (height / 2), 0, 20);
    entities.push_back(ship);
    /*
for(int i=0;i<1;i++)
{
    enemyShip = new EnemyShip(ship);
    enemyShip->initializer(width,height,enemyShipAnim_M, (rand()%width)+width, (rand()%height)+height,rand()%360, 20);
    entities.push_back(enemyShip);
    enemies.push_back(enemyShip);
}*/
    gameLoop();

    /*for(auto entity:entities){ ///en esta parte auto le asigna el tipo *Asteroid
        delete (entity);
    }*/
    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity *e = *i;
        delete e;
        i = entities.erase(i);
    }

    gameOverScreen();
}

void Game::gameLoop()
{
    while (window1.isOpen() && !gameOver)
    {

        eventListener();
        time++;
        //int asd=fps.getFps();

        if (updateFps)
        {
            frameTime += getFrameTime();
            updateFps = false;
            fpsText.setString("fps: " + std::to_string(1 / (frameTime / 2)));
        }
        else
        {
            frameTime = getFrameTime();
            updateFps = true;
        }

        ///gotoxy(0,0);std::cout<<"                                                            ";
        ///gotoxy(0,0);std::cout<<"frametime: "<< frameTime*1000<<"ms Fps: "<< (int)(1/frameTime) <<std::endl;

        //aca hacer que pasen las cosas que pasan

        if (time % 60 == 0)
        {
            score++;
        }
        ///std::cout<<asteroidNumber<<std::endl;

        if (time % 150 == 0 && asteroidNumber <= 4)
        {

            for (int i = 0; i < 3; i++)
            {
                asteroidNumber++;
                Asteroid *a = new Asteroid();
                sf::Vector2i pos = randomGenerator();
                a->initializer(width, height, asteroidAnim, pos.x, pos.y, rand() % 360, 25);
                entities.push_back(a);
            }
        }

        if (time % 300 == 0)
        {
            if (enemiesNumber <= 2)
            {
                enemiesNumber++;
                enemyShip = new EnemyShip(ship);
                sf::Vector2i pos = randomGenerator();
                enemyShip->initializer(width, height, enemyShipAnim_M, pos.x, pos.y, rand() % 360, 20);
                entities.push_back(enemyShip);
            }
            if (numberOfCosos <= 2)
            {
                numberOfCosos++;
                Entity *g = new Entity();
                g->initializer(111, 111, cosoMisteriosoAnim, rand() % width, rand() % height, 270, 26);
                g->setName("coso++");
                entities.push_back(g);
            }
        }

        for (auto i = entities.begin(); i != entities.end();)
        {
            Entity *e = *i;

            e->update();
            e->updateAnim();

            if (e->getName().compare("enemy") == 0)
            {
                if( ((EnemyShip*) e)->isShooting() )
                {
                    shotSound2.play();
                    for (int i = -1; i <= 1; i++)
                    {
                        Bullet *f = new Bullet(true);
                        f->initializer(width, height, enemyBulletAnim, e->getPos().x, e->getPos().y, e->getAngle() + (i * 3), 10);
                        entities.push_back(f);
                    }
                }

            }


            checkColition(e);
            if (e->getName().compare("explosion") == 0)
            {
                if (e->isEndAnim())
                {
                    e->setLife(0);
                }
            }

            if (e->getLife() == 0)
            {
                if (e->getName().compare("asteroid") == 0)
                {
                    score++;
                    asteroidNumber--;

                    explosionSound.play();

                    Entity *g = new Entity();
                    g->initializer(111, 111, explosionAnimC, e->getPos().x, e->getPos().y);
                    g->setName("explosion");
                    entities.push_back(g);
                }
                if (e->getName().compare("player") == 0)
                {
                    ///gameOverScreen();///muestra el score y lo guarda si es mayor al maximo
                    gameOver = true;
                }
                if (e->getName().compare("enemy") == 0)
                {
                    explosionSound.play();
                    score += 10;
                    enemiesNumber--;

                    Entity *g = new Entity();
                    g->initializer(111, 111, explosionAnimB, e->getPos().x, e->getPos().y);
                    g->setName("explosion");
                    entities.push_back(g);
                }
                delete e;
                i = entities.erase(i);
            }
            else
            {
                i++;
            }
        }
        scoreText.setString(highScoreString + std::to_string(score));
        drawWindow();
    }
}

void Game::checkColition(Entity *a)
{
    for (auto b : entities)
    {
        if (a->getName().compare("bullet") == 0)
        {
            if (b->getName().compare("asteroid") == 0)
            {
                if (isCollide(a, b))
                {
                    a->setLife(0);
                    b->setLife(0);
                }
            }
            else if (b->getName().compare("enemy") == 0)
            {
                if (isCollide(a, b))
                {
                    a->setLife(0);
                    b->setLife(0);
                }
            }
            else if (b->getName().compare("enemyBullet") == 0)
            {
                if (isCollide(a, b))
                {
                    a->setLife(0);
                    b->setLife(0);
                    {
                        explosionSound2.play();
                        Entity *g = new Entity();
                        g->initializer(111, 111, explosionAnimA, b->getPos().x, b->getPos().y);
                        g->setName("explosion");
                        entities.push_back(g);
                    }
                }
            }
        }
        if (a->getName().compare("player") == 0)
        {
            if (b->getName().compare("asteroid") == 0)
            {
                if (isCollide(a, b))
                {
                    a->setLife(0);
                    b->setLife(0);
                }
            }
            else if (b->getName().compare("enemy") == 0)
            {
                if (isCollide(a, b))
                {
                    a->setLife(0);
                    b->setLife(0);
                }
            }
            else if (b->getName().compare("enemyBullet") == 0)
            {
                if (isCollide(a, b))
                {
                    a->setLife(0);
                    b->setLife(0);
                }
            }
            else if (b->getName().compare("coso++") == 0)
            {
                if (isCollide(a, b))
                {
                    b->setLife(0);
                    ship->addFeed(30);
                    numberOfCosos--;
                }
            }
        }
    }
}

void Game::eventListener()
{

    while (window1.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window1.close();
    }

    //aca comprobar lo que pasa
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship->rotatexd(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship->rotatexd(-3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ship->advanceShip(true);
        ship->setAnim(shipAnim_M);
    }
    else
    {
        (ship->advanceShip(false), ship->setAnim(shipAnim));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        ship->setAngle(270);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        ship->setAngle(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        ship->setAngle(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        ship->setAngle(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (bulletCoolDown % 3 == 0)
        {
            if (ship->isFeeded() == true)
            {
                ship->addFeed(-1);
                for (int i = -1; i <= 1; i++)
                {
                    Bullet *f = new Bullet();
                    f->initializer(width, height, bulletAnim, ship->getPos().x, ship->getPos().y, ship->getAngle() + (i * 3), 10);
                    entities.push_back(f);
                }
            }

            shotSound1.play();
            Bullet *b = new Bullet;
            b->initializer(width, height, bulletAnim, ship->getPos().x, ship->getPos().y, ship->getAngle(), 10);
            entities.push_back(b);
        }
        bulletCoolDown++;
    }
    else
    {
        bulletCoolDown++;
    }
    if (bulletCoolDown == 1000)
        bulletCoolDown = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        ///gameOver=true;
        pauseMenu();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        std::cout << ship->getAngle();
    }
}
void Game::drawWindow()
{
    window1.clear();

    window1.draw(background);
    window1.draw(scoreText);

    for (auto entity : entities)
    {
        entity->draw(window1);
    }
    window1.draw(fpsText);

    //ship->draw(window1);

    window1.display();
}
float Game::getFrameTime()
{
    currentTime = clock.getElapsedTime();
    clock.restart();
    return currentTime.asSeconds();
}

bool Game::isCollide(Entity *a, Entity *b)
{
    float dDifX = (a->getPos().x - b->getPos().x);
    float dDifY = (a->getPos().y - b->getPos().y);
    float distancia = sqrt(pow(dDifX, 2) + pow(dDifY, 2));
    return distancia < (a->getRadius() + b->getRadius());
}
int Game::readHighestScore()
{
    int leyo;
    int regint;
    FILE *p;
    p = fopen("highScore.dat", "rb");
    if (p == NULL)
        return -1;
    fseek(p, 0, 0); ///es lo mismo que fseek(p,sizeof (regint)*0,0);
    leyo = fread(&regint, sizeof regint, 1, p);
    fclose(p);
    if (leyo == 0)
        return -2;
    return regint;
}
void Game::saveScore(int score)
{
    if (score > readHighestScore())
    {
        FILE *p;
        p = fopen("highScore.dat", "wb");
        if (p == NULL)
            return;
        fwrite(&score, sizeof(score), 1, p);
        fclose(p);
    }
}
void Game::gameOverScreen()
{

    sf::Font font;
    font.loadFromFile("fonts/PressStart2P-Regular.ttf");
    SelectableText backButton;
    sf::Text title;
    //sf::Text score;
    sf::Text highScoreText;
    sf::Text yourScoreText;
    sf::Text newHighScoreText;
    std::string yourScore;
    std::string highScore;
    std::string newHighScore;
    std::string scoreString = std::to_string(score) + "pts";

    highScoreText.setFont(font);
    yourScoreText.setFont(font);
    title.setFont(font);
    newHighScoreText.setFont(font);
    //score.setFont(font);
    highScoreText.setColor(sf::Color(255, 255, 255));
    yourScoreText.setColor(sf::Color(255, 255, 255));
    title.setColor(sf::Color(255, 255, 255));
    newHighScoreText.setColor(sf::Color(255, 255, 255));
    //score.setColor(sf::Color(255,255,255));

    std::string highScoreString;

    highScoreString = readHighestScore() >= 0 ? std::to_string(readHighestScore()) + "pts" : (language.compare("es") == 0 ? "No hay puntajes registrados" : "No scores recorded");

    /*score.setString(highScoreString);
    score.setOrigin(score.getGlobalBounds().width/2 , score.getGlobalBounds().height/2);
    score.setPosition(width/2,height/2);*/

    if (language.compare("en") == 0)
    {
        backButton.initializer("Back", (50 * 3) + 25, height - 50, font, 50);
        title.setString("Game Over");
        newHighScore = "New high score saved";
        title.setCharacterSize(45);
        yourScore = "Your score: ";
        highScore = "Best score: ";
    }
    else if (language.compare("es") == 0)
    {
        backButton.initializer("Volver", (50 * 3) + 25, height - 50, font, 50);
        title.setString("Juego Terminado");
        newHighScore = "Nueva puntuaci\xF3n m\xE1xima guardada";
        title.setCharacterSize(45);
        yourScore = "Tu puntuacion: ";
        highScore = "Mejor puntuacion: ";
    }

    yourScoreText.setString(yourScore + scoreString);
    yourScoreText.setOrigin(yourScoreText.getGlobalBounds().width / 2, yourScoreText.getGlobalBounds().height / 2);
    yourScoreText.setPosition(width / 2, height * (0.4));

    highScoreText.setString(highScore + highScoreString);
    highScoreText.setOrigin(highScoreText.getGlobalBounds().width / 2, highScoreText.getGlobalBounds().height / 2);
    highScoreText.setPosition(width / 2, height * (0.6));

    if (score > readHighestScore())
    {
        newHighScoreText.setString(newHighScore);
        saveScore(score);
    }
    newHighScoreText.setOrigin(newHighScoreText.getGlobalBounds().width / 2, newHighScoreText.getGlobalBounds().height / 2);
    newHighScoreText.setPosition(width / 2, height * (0.8));

    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(width / 2, 50);
    bool exit1 = false;
    while (window1.isOpen() && !exit1)
    {
        sf::Event event1;
        while (window1.pollEvent(event1))
        {
            if (event1.type == sf::Event::Closed)
                window1.close();
            if (event1.type == sf::Event::MouseMoved)
            {
                if (backButton.checkMouseColition(window1))
                {
                    backButton.updateSelection(true);
                }
                else
                {
                    backButton.updateSelection(false);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                exit1 = true;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backButton.checkMouseColition(window1))
            {
                exit1 = true;
            }
        }

        backButton.update();

        window1.clear();
        backButton.draw(window1);
        window1.draw(title);
        ///window1.draw(score);
        window1.draw(yourScoreText);
        window1.draw(highScoreText);
        window1.draw(newHighScoreText);
        window1.display();
    }
}

void Game::pauseMenu()
{
    window1.setFramerateLimit(60);

    sf::Text title;
    title.setFont(font);
    title.setColor(sf::Color(255, 255, 255));

    if (language.compare("en") == 0)
    {
        resumeButton.initializer("Resume", width / 2, height * 0.3, font, 50);
        exitButton.initializer("Exit", width / 2, height * 0.6, font, 50);
        title.setString("Game paused");
        title.setCharacterSize(45);
    }
    else if (language.compare("es") == 0)
    {
        resumeButton.initializer("Reanudar", width / 2, height * 0.3, font, 50);
        exitButton.initializer("Salir", width / 2, height * 0.6, font, 50);
        title.setString("Juego pausado");
        title.setCharacterSize(45);
    }
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(width / 2, 50);
    bool exit = false;
    int timePaused = 0;
    int x = 0;
    while (window1.isOpen() && x < 180)
    {
        if (timePaused < 100)
        {
            timePaused++;
            std::cout << timePaused;
        }
        if (exit == false)
        {
            sf::Event event1;
            while (window1.pollEvent(event1))
            {
                if (event1.type == sf::Event::Closed)
                    window1.close();
                if (event1.type == sf::Event::MouseMoved)
                {
                    if (resumeButton.checkMouseColition(window1))
                    {
                        resumeButton.updateSelection(true);
                    }
                    else
                    {
                        resumeButton.updateSelection(false);
                    }
                    if (exitButton.checkMouseColition(window1))
                    {
                        exitButton.updateSelection(true);
                    }
                    else
                    {
                        exitButton.updateSelection(false);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && timePaused > 30)
                {
                    exit = true;
                }
                if (resumeButton.isClicked(window1))
                {
                    exit = true;
                }
                if (exitButton.isClicked(window1))
                {
                    gameOver = true;
                    exit = true;
                }
            }

            resumeButton.update();
            exitButton.update();

            window1.clear();
            resumeButton.draw(window1);
            exitButton.draw(window1);
            window1.draw(title);
            window1.display();
        }
        else
        {
            x++;
            std::cout << x << std::endl;
        }
    }
}
sf::Vector2i Game::randomGenerator()
{
    int x, y;
    bool random1 = rand() % 2;
    bool random2 = rand() % 2;
    if (random1)
    {
        y = height * rand() % 2;
        x = rand() % width;
    }
    else
    {
        y = height * rand() % 2;
        x = rand() % width;
    }
    return sf::Vector2i(x, y);
}
