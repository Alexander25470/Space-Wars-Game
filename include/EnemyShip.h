#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>



class EnemyShip: public Entity
{
    Entity *target;
    bool pointingTarget;
    int bulletCoolDown;
    bool shooting;


    public:
        EnemyShip(Entity *_target);
        void update();
        bool isShooting();


};


