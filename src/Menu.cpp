#include "Menu.h"

Menu::Menu(short int _width, short int _height, std::string title):window1(sf::VideoMode(_width, _height), title)
{
    width=_width;
    height=_height;
    j=0;
    k=0;
    sf::Font font;
    font.loadFromFile("fonts\\arial.ttf");
    text= new sf::Text[3];
//------------------------------------------------------------------------------
    text[0].setFont(font);
    text[0].setColor(sf::Color::White);
    text[0].setString("play");
    text[0].setCharacterSize(24);
    text[0].setPosition(width/2,height/3);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString("options");
    text[1].setCharacterSize(24);
    text[1].setPosition(width/2,height/3+height*0.10);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString("exit");
    text[2].setCharacterSize(24);
    text[2].setPosition(width/2,height/3+height*0.20);
//------------------------------------------------------------------------------



    //aca inicializar las cosas
    window1.setFramerateLimit(60);
    //cargo imagen de fondo
    backgroundTexture.loadFromFile("images\\spritesheet.png");
    /*sf::Sprite asd(backgroundTexture,sf::IntRect(0,0,1500,900));
    background=asd;*/
    //termina de cargar la imagen de fondo


    gameLoop();
    delete text;
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

                if(text[0].getGlobalBounds().contains(mousePos.x,mousePos.y))
                    text[0].setColor(sf::Color::Green);
                else
                    text[0].setColor(sf::Color::White);
                if(text[1].getGlobalBounds().contains(mousePos.x,mousePos.y))
                    text[1].setColor(sf::Color::Green);
                else
                    text[1].setColor(sf::Color::White);
                if (text[2].getGlobalBounds().contains(mousePos.x,mousePos.y))
                    text[2].setColor(sf::Color::Green);
                else
                    text[2].setColor(sf::Color::White);

            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && text[0].getGlobalBounds().contains(mousePos.x,mousePos.y))
                    {
                        Game partida_l(width,height,window1);
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
    window1.draw(text[0]);
    window1.draw(text[1]);
    window1.draw(text[2]);
    window1.display();
}
