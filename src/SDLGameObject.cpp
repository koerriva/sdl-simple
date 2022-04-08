#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* params):GameObject(params){
    this->m_x = params->getX();
    this->m_y = params->getY();

    this->m_width = params->getWidth();
    this->m_height = params->getHeight();
    
    this->m_textureID = params->getTextureID();

    this->m_currentFrame = 1;
    this->m_currentRow = 1;
}

void SDLGameObject::draw(){
    TextureManager::Instance()->drawFrame(m_textureID,m_x,m_y,m_width,m_height,m_currentRow,m_currentFrame,Game::Instance()->getRenderer());
}

void SDLGameObject::update(){

}

void SDLGameObject::clean(){

}