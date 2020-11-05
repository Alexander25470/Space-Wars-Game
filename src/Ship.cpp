#include "Ship.h"
#include <math.h>
#include <iostream>
Ship::Ship()
{
    setName("player");
}


void Ship::advanceShip(bool _move)
{
    if(_move)
    {
        increaseDist(cos(getAngle()*(M_PI/180))*0.1,sin(getAngle()*(M_PI/180))*0.1);

    }
    else
    {
    setDist(getDistxy().x*0.99,getDistxy().y*0.99);
    }

    int maxSpeed=16;
    float speed = sqrt(getDistxy().x*getDistxy().x+getDistxy().y*getDistxy().y);
    if (speed>maxSpeed)
     {
         increaseDist(maxSpeed/speed,maxSpeed/speed,2);

     }

    updatePos(getDistxy().x,getDistxy().y);
    sf::Vector2f _Pos = getPos();
    if(_Pos.x>1280/*width*/) setPos(0, _Pos.y);
    if(_Pos.y>720/*height*/) setPos(_Pos.x,0);
    if(_Pos.x<0) setPos(1280, _Pos.y);
    if(_Pos.y<0) setPos(_Pos.x,720);

}
