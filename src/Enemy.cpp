#include "Enemy.h"
#include "Game.h"
#include "TextureManager.h"

Enemy::Enemy(const LoaderParams* params):SDLGameObject(params){
    m_velocity = {0,0};
}

void Enemy::draw(){
    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();
    if(m_enemyFace==LEFT){
        textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer);
    }

    if(m_enemyFace==RIGHT){
        textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer,SDL_FLIP_HORIZONTAL);
    }
}

void Enemy::update(){
    m_currentFrame = int((SDL_GetTicks()/100)%4);

    SDLGameObject::update();
}

void Enemy::clean(){
    SDLGameObject::clean();
}