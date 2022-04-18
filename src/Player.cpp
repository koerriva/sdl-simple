#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"

Player::Player():SDLGameObject(){

}

void Player::load(const LoaderParams* params){
    SDLGameObject::load(params);

    renderOffset.spriteOffsetX = params->getSpriteOffsetX();
    renderOffset.spriteOffsetY = params->getSpriteOffsetY();
    
    m_velocity = ivec2(0,0);

    m_collisionRect.x += m_position.x;
    m_collisionRect.y += m_position.y;
}

void Player::draw(){
    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();
    if(m_playerFace==LEFT){
        textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer,SDL_FLIP_NONE,renderOffset);
    }

    if(m_playerFace==RIGHT){
        textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer,SDL_FLIP_HORIZONTAL,renderOffset);
    }

    SDL_SetRenderDrawColor(renderer, 15, 255, 15, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer,&m_collisionRect);
}

void Player::update(){
    m_velocity = ivec2(0,0);

    handleInput();

    m_currentFrame = int((SDL_GetTicks()/100)%m_numFrames);

    if(m_velocity.x>0){
        m_playerFace = LEFT;
    }
    if(m_velocity.x<0){
        m_playerFace = RIGHT;
    }

    SDLGameObject::update();
}

void Player::clean(){
    SDLGameObject::clean();
}

void Player::handleInput(){
    auto ih = InputHandler::Instance();
    if(ih->joysticksInitialised()){
        vec2 leftLR = ih->axis(0,1);
        vec2 leftUD = ih->axis(0,2);

        if(leftLR.x!=0){
            m_velocity.x = leftLR.x;
        }

        if(leftLR.y!=0){
            m_velocity.y = leftLR.y;
        }

        if(leftUD.x!=0){
            m_velocity.x = leftUD.x;
        }

        if(leftUD.y!=0){
            m_velocity.y = leftUD.y;
        }

        //button Y of the XOBX 360 Controller
        if(ih->getButtonState(0,3)){
            m_velocity.x = 1;
        }
    }

    if(ih->getMouseButtonState(MIDDLE)){
        m_velocity.x = 1;
    }

    // m_velocity = (ih->getMousePosition()-m_position)/100;
    if(ih->isKeyDown(SDL_SCANCODE_RIGHT)){
        m_velocity.x = 2;
    }
    if(ih->isKeyDown(SDL_SCANCODE_LEFT)){
        m_velocity.x = -2;
    }
    if(ih->isKeyDown(SDL_SCANCODE_UP)){
        m_velocity.y = -2;
    }
    if(ih->isKeyDown(SDL_SCANCODE_DOWN)){
        m_velocity.y = 2;
    }
}