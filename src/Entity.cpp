#include "Entity.h"

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
     ///anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);

     /*CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     app.draw(circle);*/
   }
