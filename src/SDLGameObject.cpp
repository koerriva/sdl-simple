#include "SDLGameObject.h"
#include "Game.h"

ShooterObject::ShooterObject():GameObject(){

}

void ShooterObject::load(std::unique_ptr<LoaderParams> const& params){
    this->m_position = ivec2(params->getX(),params->getY());
    this->m_velocity = ivec2(0,0);

    this->m_width = params->getWidth();
    this->m_height = params->getHeight();
    
    this->m_textureID = params->getTextureID();

    this->m_currentFrame = 1;
    this->m_currentRow = 1;

    this->m_numFrames = params->getNumFrames();

    this->m_collision = params->getCollision();
}

void ShooterObject::draw(){
    TextureManager::Instance()->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,Game::Instance()->getRenderer(),m_angle,m_alpha,SDL_FLIP_NONE);
}

void ShooterObject::update(){
    m_position += m_velocity;
    m_velocity += m_acceleration;
}

void ShooterObject::clean() {

}

void ShooterObject::collision() {

}

void ShooterObject::doDyingAnimation(){
    m_currentFrame = int((SDL_GetTicks()/100)%m_numFrames);

    if(m_dyingCounter == m_dyingTime){
        m_dead = true;
    }

    m_dyingCounter++;
}