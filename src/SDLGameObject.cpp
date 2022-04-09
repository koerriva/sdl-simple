#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* params):GameObject(params){
    this->m_position = ivec2(params->getX(),params->getY());
    this->m_velocity = ivec2(0,0);

    this->m_width = params->getWidth();
    this->m_height = params->getHeight();
    
    this->m_textureID = params->getTextureID();

    this->m_currentFrame = 1;
    this->m_currentRow = 1;
}

void SDLGameObject::draw(){
    TextureManager::Instance()->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,Game::Instance()->getRenderer());
}

void SDLGameObject::update(){
    m_position += m_velocity;
    m_velocity += m_acceleration;
}

void SDLGameObject::clean(){

}