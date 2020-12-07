#include "SelectableText.h"
#include <iostream>
SelectableText::SelectableText()
{


}

void SelectableText::initializer(std::string text, int x, int y, sf::Font &font, int _size, int type)
{

    _font=font;

    //_text= sf::Text;
    _text.setString(text);

    _text.setFont(_font);
    _text.setCharacterSize(_size);

    _text.setOrigin(_text.getGlobalBounds().width/2 , _text.getGlobalBounds().height/2);
    _text.setPosition(x,y);


    if(type==1)
    {
        _text.setFillColor(sf::Color(0, 255, 0));
        _text.setOutlineThickness(20.0f);
        _text.setOutlineColor(sf::Color(0, 255, 0));
        _text.setOutlineThickness(2.0f);

    }
        selectSoundBuffer.loadFromFile("sounds\\menuback.wav");
        selectSound.setBuffer(selectSoundBuffer);
        selectSound.setVolume(vol);
        clickSoundBuffer.loadFromFile("sounds\\menuhit.wav");
        clickSound.setBuffer(clickSoundBuffer);
        clickSound.setVolume(vol);
}

void SelectableText::draw(sf::RenderWindow &app)
{
    app.draw(_text);
}

bool SelectableText::checkMouseColition(sf::RenderWindow &window)
{
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    //_selected=(_text.getGlobalBounds().contains(mousePosition));
    return (_text.getGlobalBounds().contains(mousePosition));
}
bool SelectableText::isClicked(sf::RenderWindow &window)
{
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    //_selected=(_text.getGlobalBounds().contains(mousePosition));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (_text.getGlobalBounds().contains(mousePosition)))
    {
        clickSound.play();
        return true;
    }else
    return false;
}

void SelectableText::update()
{
    if(_selected)
    {
        _text.setColor(sf::Color(0,255,0));
    }else
    {
        _text.setColor(sf::Color(255,255,255));
    }
}
void SelectableText::updateSelection(bool selected)
{
    if( selected && !_selected)
    {
        selectSound.play();
    }
    _selected=selected;
}
void SelectableText::updateString(std::string _string)
{
    _text.setString(_string);
}
bool SelectableText::isSelected()
{
    return _selected;
}
