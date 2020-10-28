#include "Game.h"

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

Game::Game(short int _width, short int _height,sf::RenderWindow &_window1):window1(_window1)
{
    gameOver=false;
    ///window1=_window1;
    width=_width;
    height=_height;

    ///aca inicializar las cosas
    window1.setFramerateLimit(60);
    ///cargo imagen de fondo
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images\\background.jpg");
    background=sf::Sprite(sf::Sprite(backgroundTexture));
    ///termina de cargar la imagen de fondo
    shape = sf::CircleShape(50.f);
    xCircle=width/2-shape.getRadius();
    yCircle=height/2-shape.getRadius();

    asteroidTexture.loadFromFile("images/rock.png");
    asteroidAnim = Animation(asteroidTexture,0,0,64,64,16,0.2);

    for(int i=0;i<15;i++)
    {
      Asteroid *a = new Asteroid();
      a->initializer(asteroidAnim, rand()%width, rand()%height, rand()%360, 25);
      asts.push_back(a);
    }


    gameLoop();

    for(astsIterator=asts.begin();astsIterator!=asts.end();astsIterator++)
        {
            delete (*astsIterator);
        }
}

void Game::gameLoop() {
    while (window1.isOpen() && !gameOver)
    {

        eventListener();
        //int asd=fps.getFps();
        frameTime=getFrameTime();

        gotoxy(0,0);std::cout<<"                                                            ";
        gotoxy(0,0);std::cout<<"frametime: "<< frameTime*1000<<"ms Fps: "<< (int)(1/frameTime) <<std::endl;

        //aca hacer que pasen las cosas que pasan
        //xCircle+=0.3f;

        /*for(auto i=asts.begin();i!=asts.end();i++)
        {
            Asteroid *e=*i;
            e->update();
        }*/

        for(astsIterator=asts.begin();astsIterator!=asts.end();astsIterator++)
        {
            (*astsIterator)->update();
        }


        shape.setPosition(xCircle,yCircle);

        drawWindow();

    }
}

void Game::drawWindow(){
    window1.clear();

    window1.draw(background);

    for(astsIterator=asts.begin();astsIterator!=asts.end();astsIterator++)
        {
            (*astsIterator)->draw(window1);
        }

    window1.draw(shape);
    window1.display();
}

void Game::eventListener() {

        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();
        }

        //aca comprobar lo que pasa
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            xCircle+=10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            xCircle-=10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            yCircle-=10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            yCircle+=10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            gameOver=true;
        }


}

float Game::getFrameTime(){
    currentTime = clock.getElapsedTime();
    clock.restart();
    return currentTime.asSeconds();
}
