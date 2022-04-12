#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* params,void(*callback)()):SDLGameObject(params){
    m_currentFrame = MOUSE_OUT;
    m_callback = callback;
}

void MenuButton::draw(){
    SDLGameObject::draw();
}

void MenuButton::update(){
    ivec2 mousePosition = InputHandler::Instance()->getMousePosition();

    if(mousePosition.x > m_position.x&&mousePosition.x < m_position.x+m_width
        &&mousePosition.y > m_position.y&&mousePosition.y < m_position.y+m_height){
        if(InputHandler::Instance()->getMouseButtonState(LEFT) && m_released){
            m_currentFrame = CLICKED;
            m_callback();
            m_released = false;
        }else if(!InputHandler::Instance()->getMouseButtonState(LEFT)){
            m_currentFrame = MOUSE_OVER;
            m_released = true;
        }
    }else{
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean(){
    SDLGameObject::clean();
}