#include "Bullet.h"

Bullet::Bullet(bool isEnemy)
{
    _isEnemy=isEnemy;
    if(_isEnemy)
    {
        setName("enemyBullet");
    }else
    {
        setName("bullet");
    }

}

void Bullet::update()
{
    if(_isEnemy)
    {
        setDist(cos(getAngle()*(MATH_PI/180))*15,sin(getAngle()*(MATH_PI/180))*15);
    }else
    {
        setDist(cos(getAngle()*(MATH_PI/180))*12,sin(getAngle()*(MATH_PI/180))*12);
    }


    updatePos();
    sf::Vector2f _Pos = getPos();
    if(_Pos.x>width/*width*/) setLife(0);
    if(_Pos.y>height/*height*/) setLife(0);
    if(_Pos.x<0) setLife(0);
    if(_Pos.y<0) setLife(0);

}
