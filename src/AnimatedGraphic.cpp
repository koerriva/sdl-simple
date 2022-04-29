#include "AnimatedGraphic.h"
#include "TextureManager.h"
#include "Game.h"

AnimatedGraphic::AnimatedGraphic():ShooterObject(){
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const& params){
    ShooterObject::load(params);
    
    this->m_animSpeed = params->getAnimSpeed();
}

void AnimatedGraphic::update(){
    m_currentFrame = int(((SDL_GetTicks()/(1000/m_animSpeed))%m_numFrames));
}

void AnimatedGraphic::draw(){
    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();
    textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer,m_angle,m_alpha,SDL_FLIP_NONE);
}

void AnimatedGraphic::clean(){
    ShooterObject::clean();
}