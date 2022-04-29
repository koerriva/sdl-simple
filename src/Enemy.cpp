#include "Enemy.h"
#include "Game.h"
#include "TextureManager.h"

Enemy::Enemy():ShooterObject(){
    
}

void Enemy::load(std::unique_ptr<LoaderParams> const& params){
    ShooterObject::load(params);

    m_velocity = {0,0};

    m_collision.x += m_position.x;
    m_collision.y += m_position.y;
}

void Enemy::draw(){
    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(m_enemyFace==RIGHT){
        flip = SDL_FLIP_HORIZONTAL;
    }
    textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer,m_alpha,m_alpha,flip);

    SDL_SetRenderDrawColor(renderer, 15, 255, 15, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer,&m_collision);
}

void Enemy::update(){
    ShooterObject::update();
    m_currentFrame = int((SDL_GetTicks()/100)%m_numFrames);
}

void Enemy::clean(){
    ShooterObject::clean();
}