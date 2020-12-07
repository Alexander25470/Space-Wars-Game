#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class SelectableText
{
        const int vol=5;
        bool _selected;
        sf::Text _text;
        sf::Font _font;
        sf::Sound selectSound;
        sf::SoundBuffer selectSoundBuffer;
        sf::Sound clickSound;
        sf::SoundBuffer clickSoundBuffer;
    public:
        SelectableText();
        void initializer(std::string, int x, int y, sf::Font &font, int _size, int type=1);
        bool isSelected();
        void update();
        bool checkMouseColition(sf::RenderWindow &window);
        void draw(sf::RenderWindow &app);
        void updateSelection(bool selected);
        void updateString(std::string _string);
        bool isClicked(sf::RenderWindow &window);
};
