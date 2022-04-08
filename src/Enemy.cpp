#include "Enemy.h"

void Enemy::update(){
    m_x += 1;
    m_y += 1;

    GameObject::update();
}