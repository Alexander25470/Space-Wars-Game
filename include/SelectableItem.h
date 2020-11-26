#pragma once
#include <SFML/Graphics.hpp>

class SelectableItem
{
        bool _selected;
        sf::Texture _texture;
        sf::Sprite sprite;
        int _w,_h,_x,_y;
    public:
        SelectableItem();
        void initializer(sf::Texture &texture, int width, int height, int x, int y);
        void isSelected(bool);
        void update();
        void draw(sf::RenderWindow &app);
        sf::Sprite getSprite(){return sprite;};
};

