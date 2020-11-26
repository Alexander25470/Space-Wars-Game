#include "Menu.h"

Menu::Menu(short int _width, short int _height, std::string title):window1(sf::VideoMode(_width, _height), title)
{
    width=_width;
    height=_height;
    j=0;
    k=0;
    sf::Texture playTexture;
    playTexture.loadFromFile("images\\menu\\PLAY.png");
    play.initializer(playTexture,329,100,width/2-(329/2),100);

    sf::Texture optionsTexture;
    optionsTexture.loadFromFile("images\\menu\\OPTIONS.png");
    options.initializer(optionsTexture,517,100,width/2-(517/2),250);


    sf::Texture quitTexture;
    quitTexture.loadFromFile("images\\menu\\QUIT.png");
    quit.initializer(quitTexture,242,100,width/2-(242/2),400);


    //aca inicializar las cosas
    window1.setFramerateLimit(60);
    //cargo imagen de fondo
    backgroundTexture.loadFromFile("images\\spritesheet.png");

    gameLoop();
}
void Menu::gameLoop(){
    while(window1.isOpen()){

        eventListener();
        //std::cout<<((int)j)<<std::endl<<" "<<((int)k)<<std::endl;
        //sf::Sprite asd(backgroundTexture,sf::IntRect(((int)j)*1500,((int)k)*900,1500,900));
        background= sf::Sprite(backgroundTexture,sf::IntRect(((int)j)*1500,((int)k)*900,1500,900));
        j+=0.1f;
        if(((int)j)==3){
            j=0;
            k+=1.0f;
            };
        if(((int)k)==6){
            j=0;
            k=0;
        }
        play.update();
        options.update();
        quit.update();


        drawWindow();
    }

}
void Menu::eventListener(){
     while (window1.pollEvent(event))
        {
            sf::Vector2i mousePos=sf::Mouse::getPosition(window1);
            if (event.type == sf::Event::Closed)
                window1.close();
            if (event.type == sf::Event::MouseMoved)
            {
                if(play.getSprite().getGlobalBounds().contains(mousePos.x,mousePos.y))
                {
                    play.isSelected(true);
                }else
                {
                    play.isSelected(false);
                }
                if(options.getSprite().getGlobalBounds().contains(mousePos.x,mousePos.y))
                {
                    options.isSelected(true);
                }else
                {
                    options.isSelected(false);
                }
                if(quit.getSprite().getGlobalBounds().contains(mousePos.x,mousePos.y))
                {
                    quit.isSelected(true);
                }else
                {
                    quit.isSelected(false);
                }

            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && play.getSprite().getGlobalBounds().contains(mousePos.x,mousePos.y))
                    {
                        Game partida_l(width,height,window1);
                    }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && quit.getSprite().getGlobalBounds().contains(mousePos.x,mousePos.y))
                {
                   window1.close();
                }

        }
//----------------------------------------------------------------------------------------------------------------------
//--------------------con este if se crea el objeto juego---------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            Game partida_l(width,height,window1);
        }
//----------------------------------------------------------------------------------------------------------------------
//--------------------con este if se crea el objeto juego---------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
void Menu::drawWindow()
{
    window1.clear();

    //aca mostrar todo lo necesario
    window1.draw(background);

    quit.draw(window1);
    play.draw(window1);
    options.draw(window1);


    window1.display();
}
