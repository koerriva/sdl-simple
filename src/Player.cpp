#include "Player.h"

void Player::update(){
    m_x += 1;
    m_currentFrame = int((SDL_GetTicks()/100)%10);
}