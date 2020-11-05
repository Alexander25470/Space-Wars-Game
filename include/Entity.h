#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Entity
{   private:
        float angle;
        float radius;
        sf::Vector2f distxy;
        bool life;
        std::string name;
        sf::Vector2f pos;
    public:
        Animation anim;
        Entity();
        void initializer(Animation &_anim, int _x,int _y, float _angle=0,int _radius=1);
        ///--------------------------------------------
        void setLife(bool _life);
        bool getLife();
        ///--------------------------------------------
        void setPos(float,float);
        sf::Vector2f getPos();
        ///--------------------------------------------
        void setDist(float,float);
        void increaseDist(float,float,unsigned short int=1);
        sf::Vector2f getDistxy();
        ///--------------------------------------------
        void setAngle(float);
        float getAngle();
        void rotatexd(float);
        ///--------------------------------------------
        void setName(std::string);
        std::string getName();
        ///--------------------------------------------
        virtual void update(){};
        void draw(sf::RenderWindow &app);
        ///--------------------------------------------
        void updatePos();


};


