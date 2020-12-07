#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
///#include


class Ship: public Entity
{
    private:
        int _feed;
    public:
        Ship();
        void advanceShip(bool);
        void update();
        bool isFeeded();
        int &feed();



};


