#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* params):SDLGameObject(params){

}

void Player::draw(){
    SDLGameObject::draw();
}

void Player::update(){
    m_velocity = ivec2(0,0);

    handleInput();

    m_currentFrame = int((SDL_GetTicks()/100)%10);

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