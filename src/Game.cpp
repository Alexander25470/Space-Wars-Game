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
    background=sf::Sprite(backgroundTexture);
    ///termina de cargar la imagen de fondo

    asteroidTexture.loadFromFile("images/rock.png");
    asteroidAnim = Animation(asteroidTexture,0,0,64,64,16,0.2);

    bulletTexture.loadFromFile("images/fire_blue.png");
    bulletAnim=Animation(bulletTexture,0,0,32,64, 16, 0.8);




    for(int i=0;i<15;i++)
    {
      Asteroid *a = new Asteroid();
      a->initializer(asteroidAnim, rand()%width, rand()%height, rand()%360, 25);
      asts.push_back(a);
    }

    shipTexture.loadFromFile("images/ship.png");
    shipTexture_M.loadFromFile("images/ship.png");
    shipAnim = Animation(shipTexture,40,0,40,40,1,0);
    shipAnim_M = Animation(shipTexture_M,40,40,40,40,1,0);

    ship.initializer(shipAnim,(width/2),(height/2),0,20);

    gameLoop();


    for(auto asts1:asts){ ///en esta parte auto le asigna el tipo *Asteroid
        delete (asts1);
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

        for(auto asts1:asts){
        asts1->update();
        asts1->anim.update();
        }



        for(auto i=bullets.begin();i!=bullets.end();)
        {
          Entity *e = *i;

          e->update();
          e->anim.update();

            if (e->getLife()==0)
            {
                i=bullets.erase(i);
                delete e;
                //std::cout<<"bala eliminada"<<std::endl;
            }
          else i++;
        }





        ship.update();


        drawWindow();

    }
}

void Game::drawWindow(){
    window1.clear();

    window1.draw(background);

    for(auto asts1:asts){
        asts1->draw(window1);
    }
    for(auto bullet:bullets){
        bullet->draw(window1);
    }


    ship.draw(window1);

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
            ship.rotatexd(3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            ship.rotatexd(-3);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            ship.advanceShip(true);
            ship.anim=shipAnim_M;
        }else
        {
            (ship.advanceShip(false),ship.anim=shipAnim);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            ship.setAngle(270);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            ship.setAngle(90);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            ship.setAngle(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            ship.setAngle(180);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Bullet *b = new Bullet;
            b->initializer(bulletAnim,ship.getPos().x,ship.getPos().y,ship.getAngle(),10);
            bullets.push_back(b);

        }
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            yCircle+=10.0f;
        }*/
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

bool Game::isCollide(Entity *a,Entity *b)
{
    float dDifX = (a->getDistxy().x - b->getDistxy().x);
    float dDifY = (a->getDistxy().y - b->getDistxy().y);
    float distancia = sqrt( pow(dDifX,2) + pow(dDifY,2) );
    return distancia < (a->getAngle() + b->getAngle());
}
