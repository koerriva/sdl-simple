#include "Enemy.h"
#include "Game.h"
#include "TextureManager.h"

Enemy::Enemy():SDLGameObject(){
    
}

void Enemy::load(const LoaderParams* params){
    SDLGameObject::load(params);

    m_velocity = {0,0};

    m_collisionRect.x = m_position.x+15;
    m_collisionRect.y = m_position.y+40;
    m_collisionRect.w = 30;
    m_collisionRect.h = 40;
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

    SDL_SetRenderDrawColor(renderer, 15, 255, 15, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer,&m_collisionRect);
}

void Enemy::update(){
    m_currentFrame = int((SDL_GetTicks()/100)%m_numFrames);
    
    SDLGameObject::update();

    m_collisionRect.x = m_position.x+15;
    m_collisionRect.y = m_position.y+40;
}

void Enemy::clean(){
    SDLGameObject::clean();
}