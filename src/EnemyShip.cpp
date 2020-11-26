#include "EnemyShip.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
EnemyShip::EnemyShip(Entity *_target)
{
    target=_target;
    pointingTarget=FALSE;
    setName("enemy");
}

void EnemyShip::update()
{
    sf::Vector2f _Pos = getPos(),targetPos = target->getPos();
    sf::Vector2f coso=targetPos-_Pos;
    float angle2=(atan2(coso.x,coso.y)*(180/MATH_PI));
    angle2=-angle2-90;
    angle2=fmodf(angle2,360);
    float fgetAngle=fmodf(getAngle() , 360 );
    if(angle2<0){
        angle2+=360;
    }
    if(fgetAngle<0){
        fgetAngle+=360;
    }
    float dif=(angle2+180) - getAngle();
    dif=fmodf(dif,360);

    if (!( (dif>=358.5f && dif<=360.0f) || (dif>=0.0f && dif<=1.5f) ))
    {
        pointingTarget=FALSE;
        if( (dif>0 && dif<180)  )
        {
            ///std::cout<<"<0"<<std::endl;
            rotatexd(3);
        }else
        {
            ///std::cout<<">0"<<std::endl;
            rotatexd(-3);
        }
    }else
    {
        pointingTarget=TRUE;
    }

    increaseDist(cos(getAngle()*(MATH_PI/180))*0.2,sin(getAngle()*(MATH_PI/180))*0.2);
    int maxSpeed=6;
    float speed = sqrt(getDistxy().x*getDistxy().x+getDistxy().y*getDistxy().y);
    if (speed>maxSpeed)
     {
         increaseDist(maxSpeed/speed,maxSpeed/speed,2);
     }

    updatePos();

    if(_Pos.x>1280/*width*/) setPos(0, _Pos.y);
    if(_Pos.y>720/*height*/) setPos(_Pos.x,0);
    if(_Pos.x<0) setPos(1280, _Pos.y);
    if(_Pos.y<0) setPos(_Pos.x,720);

}
bool EnemyShip::isPointingTarget()
{
    return pointingTarget;
}
