#pragma once
#include <Entity.h>
#include <SFML/Graphics.hpp>
///#include


class Ship: public Entity
{
    private:


    public:
        Ship();
        void advanceShip(bool);
        void update();


};


