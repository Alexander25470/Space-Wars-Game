#include "Asteroid.h"


Asteroid::Asteroid()
{
    int x=rand()%8-4;
    int y=rand()%8-4;
    while(x==0){
        x=rand()%8-4;
    }
    while(y==0){
        y=rand()%8-4;
    }

    setDist(x,y);
    setName("asteroid");
}

void Asteroid::update()
{
    anim.update();

    sf::Vector2f _Pos = getPos();

    setPos(getDistxy().x+_Pos.x,getDistxy().y+_Pos.y);

    if(_Pos.x>1280/*width*/) setPos(0, _Pos.y);
    if(_Pos.y>720/*height*/) setPos(_Pos.x,0);
    if(_Pos.x<0) setPos(1280, _Pos.y);
    if(_Pos.y<0) setPos(_Pos.x,720);



}
