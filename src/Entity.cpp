#include "Entity.h"
#include <iostream>
Entity::Entity()
{

life=1;

}

void Entity::initializer(Animation &_anim, int _x,int _y, float _angle,int _radius)
{
    anim = _anim;
    pos.x =_x; ///posicion en x
    pos.y = _y; /// posicion en y
    angle = _angle; /// angulo donde mira
    radius = _radius; /// radio del objeto

}

///-----------------LIFE----------------------
void Entity::setLife(bool _life)
{
    life = _life;
}

bool Entity::getLife()
{
    return life;
}

///-----------------DIST-----------------------
void Entity::setDist(float _distx,float _disty)
{
    distxy.x = _distx;
    distxy.y = _disty;
}
void Entity::increaseDist(float _distx,float _disty,unsigned short int type)
{
    if(type==1)
    {
        distxy.x += _distx;
        distxy.y += _disty;
    }else
    {
            if(type==2)
        {
            distxy.x *= _distx;
            distxy.y *= _disty;
        }
    }
}

sf::Vector2f Entity::getDistxy()
{
    return distxy;
}

///--------------------POS---------------------
void Entity::setPos(float _x,float _y)
{
    pos.x=_x;
    pos.y=_y;
}

sf::Vector2f Entity::getPos()
{
    return pos;
}
///--------------------POS---------------------
void Entity::updatePos()
{
    pos.x+=distxy.x;
    pos.y+=distxy.y;
}

///--------------------ANGLE-------------------

void Entity::setAngle(float _angle)
{
    angle=_angle;
}

float Entity::getAngle()
{
    return angle;
}

void Entity::rotatexd(float rotation)
{
    angle+=rotation;
    angle=(float)((int)angle%360);
    if(angle>360){
        angle+=360;
    }
}


///--------------------NAME--------------------
void Entity::setName(std::string _name)
{
    name = _name;
}

std::string Entity::getName()
{
    return name;
}

///--------------------DRAW--------------------
void Entity::draw(sf::RenderWindow &app)
   {
     anim.sprite.setPosition(pos.x,pos.y);
     anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);

     /*sf::CircleShape circle(radius);
     circle.setFillColor(sf::Color(255,0,0,170));
     circle.setPosition(pos.x,pos.y);
     circle.setOrigin(radius,radius);
     app.draw(circle);*/
   }
