#include "Bullet.h"

Bullet::Bullet()
{
    setName("bullet");
}

void Bullet::update()
{
    setDist(cos(getAngle()*(MATH_PI/180))*10,sin(getAngle()*(MATH_PI/180))*10);

    updatePos();
    sf::Vector2f _Pos = getPos();
    if(_Pos.x>1280/*width*/) setLife(0);
    if(_Pos.y>720/*height*/) setLife(0);
    if(_Pos.x<0) setLife(0);
    if(_Pos.y<0) setLife(0);

}
