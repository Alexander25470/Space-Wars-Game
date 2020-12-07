#include "EnemyShip.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
EnemyShip::EnemyShip(Entity *_target)
{
    target=_target;
    pointingTarget=false;
    setName("enemy");
    bulletCoolDown=0;
    shooting=true;
}

void EnemyShip::update()
{
    sf::Vector2f _Pos = getPos(),targetPos = target->getPos();
    sf::Vector2f coso=targetPos-_Pos;
    float angle2=(atan2(coso.x,coso.y)*(180/MATH_PI));
///-------------------------------------------
///    angulo de la nave respecto al objetivo
///-------------------------------------------
    angle2=fmodf(angle2,360);
    std::cout<<angle2<<"||";

    //angle2=-(angle2+90)-180;
    //angle2=-angle2-90-180;
    angle2=-angle2-270;
    std::cout<<angle2<<std::endl;

    float fgetAngle=fmodf(getAngle() , 360 );
///-------------------------------------------
///            los vuelvo positivos
///-------------------------------------------
    if(angle2<0){
        angle2+=360;
    }
    if(fgetAngle<0){
        fgetAngle+=360;
    }
///-------------------------------------------
/// angulo al que deberia apuntar
///-------------------------------------------
    float dif=(angle2) - fgetAngle;
    dif=fmodf(dif,360);
///-------------------------------------------
///   calcula si está en el rango de disparo
///-------------------------------------------
    if (!( (dif>=358.5f && dif<=360.0f) || (dif>=0.0f && dif<=1.5f) ))
    {
        pointingTarget=false;
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
        pointingTarget=true;
    }

    increaseDist(cos(getAngle()*(MATH_PI/180))*0.2,sin(getAngle()*(MATH_PI/180))*0.2);
    int maxSpeed=6;
    float speed = sqrt(getDistxy().x*getDistxy().x+getDistxy().y*getDistxy().y);
    if (speed>maxSpeed)
     {
         increaseDist(maxSpeed/speed,maxSpeed/speed,2);
     }

    updatePos();

    if(_Pos.x>width/*width*/) setPos(0, _Pos.y);
    if(_Pos.y>height/*height*/) setPos(_Pos.x,0);
    if(_Pos.x<0) setPos(width, _Pos.y);
    if(_Pos.y<0) setPos(_Pos.x,height);

if (pointingTarget)
{
    if(bulletCoolDown%8==0)
    {
        shooting=true;
    }else
    {
        shooting=false;
    }
    bulletCoolDown++;

}else
{
    bulletCoolDown++;
    shooting=false;
}
if(bulletCoolDown==1000) bulletCoolDown=0;
}


bool EnemyShip::isShooting()
{
    return shooting;
}


/*sf::Vector2f _Pos = getPos(),targetPos = target->getPos();
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
    dif=fmodf(dif,360);*/
