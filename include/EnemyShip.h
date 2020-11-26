#pragma once
#include <Entity.h>
#include <SFML/Graphics.hpp>
#include <windows.h>


class EnemyShip: public Entity
{
    Entity *target;
    BOOL pointingTarget;


    public:
        EnemyShip(Entity *_target);
        void update();
        bool isPointingTarget();


};


