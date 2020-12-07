#pragma once
#include "Entity.h"

class Bullet: public Entity
{
    bool _isEnemy;
    public:
        Bullet(bool isEnemy=false);
        void update();

};

