#include "Enemy.h"

Enemy::Enemy(const LoaderParams* params):SDLGameObject(params){

}

void Enemy::draw(){
    SDLGameObject::draw();
}

void Enemy::update(){
    m_velocity.x = 1;
    m_velocity.y = 1;
    m_currentFrame = int((SDL_GetTicks()/100)%6);

    SDLGameObject::update();
}

void Enemy::clean(){
    SDLGameObject::clean();
}