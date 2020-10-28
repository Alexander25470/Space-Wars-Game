#include "Animation.h"

Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed)
{
   frame = 0;
     speed = Speed;

     for (int i=0;i<count;i++)
      frames.push_back( sf::IntRect(x+i*w, y, w, h)  );

     sprite.setTexture(t);
     sprite.setOrigin(w/2,h/2);
     sprite.setTextureRect(frames[0]);
}


void Animation::update()
{
    frame += speed;
    int n = frames.size();
    if (frame >= n) frame -= n;
    if (n>0) sprite.setTextureRect( frames[int(frame)] );
}

