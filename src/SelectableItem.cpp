#include "SelectableItem.h"

SelectableItem::SelectableItem()
{

}

void SelectableItem::initializer(sf::Texture &texture, int width, int height, int x, int y)
{
    _x=x;
    _y=y;
    _w=width;
    _h=height;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,_h,_w,_h));
    sprite.setPosition(x,y);


}

void SelectableItem::isSelected(bool selected)
{
    _selected=selected;
}

void SelectableItem::update()
{
    if(_selected)
    {
        sprite.setTextureRect(sf::IntRect(0,_h,_w,_h));
        sprite.setPosition(_x,_y);
    }else
    {
        sprite.setTextureRect(sf::IntRect(0,0,_w,_h));
        sprite.setPosition(_x,_y);
    }
}
///--------------------DRAW--------------------
void SelectableItem::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}
