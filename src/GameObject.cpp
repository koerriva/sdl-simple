#include "GameObject.h"
#include "TextureManager.h"

void GameObject::load(int x,int y,int width,int height,std::string textureId){
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_textureID = textureId;

    m_currentFrame = 1;
    m_currentRow = 1;
}

void GameObject::draw(SDL_Renderer* renderer){
    TextureManager::Instance()->drawFrame(m_textureID,m_x,m_y,m_width,m_height,m_currentRow,m_currentFrame,renderer);
}

void GameObject::update(){
    m_currentFrame = int((SDL_GetTicks()/100)%6);
}

void GameObject::clean(){

}