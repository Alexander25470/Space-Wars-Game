#include "Bullet.h"

Bullet::Bullet()
{
    setName("bullet");
}

void Bullet::update()
{
    setDist(cos(getAngle()*(M_PI/180))*8,sin(getAngle()*(M_PI/180))*8);

    updatePos(getDistxy().x,getDistxy().y);
    sf::Vector2f _Pos = getPos();
    if(_Pos.x>1280/*width*/) setLife(0);
    if(_Pos.y>720/*height*/) setLife(0);
    if(_Pos.x<0) setLife(0);
    if(_Pos.y<0) setLife(0);

}
