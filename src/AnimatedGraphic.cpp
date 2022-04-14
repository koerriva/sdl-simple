#include "AnimatedGraphic.h"
#include "TextureManager.h"
#include "Game.h"

AnimatedGraphic::AnimatedGraphic():SDLGameObject(){
}

void AnimatedGraphic::load(const LoaderParams* params){
    SDLGameObject::load(params);
    
    this->m_animSpeed = params->getAnimtedSpeed();
}

void AnimatedGraphic::update(){
    m_currentFrame = int(((SDL_GetTicks()/(1000/m_animSpeed))%m_numFrames));
}

void AnimatedGraphic::draw(){
    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();
    textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer);
}

void AnimatedGraphic::clean(){
    SDLGameObject::clean();
}