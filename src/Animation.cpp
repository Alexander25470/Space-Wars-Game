#include "Animation.h"

Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed)
{
    frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
        frames.push_back(sf::IntRect(x + i * w, y, w, h));

    setTexture(t);
    setOrigin(w / 2, h / 2);
    setTextureRect(frames[0]);
}

void Animation::update()
{
    frame += speed;
    int n = frames.size();
    if (frame >= n)
        frame -= n;
    if (n > 0)
        this->setTextureRect(frames[int(frame)]);
}

bool Animation::isEnd()
{
    return frame + speed >= frames.size();
}
