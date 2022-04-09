#include "InputHandler.h"
#include <iostream>
#include "Game.h"

InputHandler* InputHandler::s_Instance = nullptr;

InputHandler::InputHandler(){
    for (size_t i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
    
}

void InputHandler::initialiseJoysticks(){
    if(SDL_WasInit(SDL_INIT_JOYSTICK)==0){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if(SDL_NumJoysticks()>0){
        for (size_t i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* joystick = SDL_JoystickOpen(i);
            if(joystick!=nullptr){
                m_joysticks.push_back(joystick);
                m_joystickValues.push_back(std::pair(vec2(0.f,0.f),vec2(0.f,0.f)));

                std::vector<bool> tmpButtons;
                for (size_t i = 0; i < SDL_JoystickNumButtons(joystick); i++)
                {
                    tmpButtons.push_back(false);
                }
                m_buttonStates.push_back(tmpButtons);
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_joysticksInitialised = true;

        std::cout << "Joystick initialise complete!" << std::endl;
    }else{
        std::cerr << "Joystick not found!" << std::endl;
    }
}

void InputHandler::update(){
    m_keyStates = SDL_GetKeyboardState(0);
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            Game::Instance()->quit();
        }

        if(event.type == SDL_JOYAXISMOTION){
            int witchOne = event.jaxis.which;

            //left stick move left or right
            if(event.jaxis.axis == 0){
                if(event.jaxis.value>m_joystickDeadZone){
                    m_joystickValues[witchOne].first.x = 1;
                }else if(event.jaxis.value<-m_joystickDeadZone){
                    m_joystickValues[witchOne].first.x = -1;
                }else{
                    m_joystickValues[witchOne].first.x = 0;
                }
            }

            //left stick move up or down
            if(event.jaxis.axis == 1){
                if(event.jaxis.value>m_joystickDeadZone){
                    m_joystickValues[witchOne].first.y = 1;
                }else if(event.jaxis.value<-m_joystickDeadZone){
                    m_joystickValues[witchOne].first.y = -1;
                }else{
                    m_joystickValues[witchOne].first.y = 0;
                }
            }

            //right stick move left or right
            if(event.jaxis.axis == 3){
                if(event.jaxis.value>m_joystickDeadZone){
                    m_joystickValues[witchOne].second.x = 1;
                }else if(event.jaxis.value<-m_joystickDeadZone){
                    m_joystickValues[witchOne].second.x = -1;
                }else{
                    m_joystickValues[witchOne].second.x = 0;
                }
            }

            //right stick move up or down
            if(event.jaxis.axis == 4){
                if(event.jaxis.value>m_joystickDeadZone){
                    m_joystickValues[witchOne].second.y = 1;
                }else if(event.jaxis.value<-m_joystickDeadZone){
                    m_joystickValues[witchOne].second.y = -1;
                }else{
                    m_joystickValues[witchOne].second.y = 0;
                }
            }
        }

        if(event.type==SDL_JOYBUTTONDOWN){
            int joy = event.jaxis.which;
            m_buttonStates[joy][event.jbutton.button] = true;
        }

        if(event.type==SDL_JOYBUTTONUP){
            int joy = event.jaxis.which;
            m_buttonStates[joy][event.jbutton.button] = false;
        }

        if(event.type==SDL_MOUSEBUTTONDOWN){
            if(event.button.button==SDL_BUTTON_LEFT){
                m_mouseButtonStates[LEFT] = true;
            }

            if(event.button.button==SDL_BUTTON_MIDDLE){
                m_mouseButtonStates[MIDDLE] = true;
            }

            if(event.button.button==SDL_BUTTON_RIGHT){
                m_mouseButtonStates[RIGHT] = true;
            }
        }

        if(event.type==SDL_MOUSEBUTTONUP){
            if(event.button.button==SDL_BUTTON_LEFT){
                m_mouseButtonStates[LEFT] = false;
            }

            if(event.button.button==SDL_BUTTON_MIDDLE){
                m_mouseButtonStates[MIDDLE] = false;
            }

            if(event.button.button==SDL_BUTTON_RIGHT){
                m_mouseButtonStates[RIGHT] = false;
            }
        }

        if(event.type==SDL_MOUSEMOTION){
            m_mousePosition.x = event.motion.x;
            m_mousePosition.y = event.motion.y;
        }
    }
}

void InputHandler::clean(){
    if(m_joysticksInitialised){
        for (auto joystick : m_joysticks){
            SDL_JoystickClose(joystick);
        }
    }
}

vec2 InputHandler::axis(int joy,int stick){
    if(m_joystickValues.size()>0){
        if(stick==1){
            return m_joystickValues[joy].first;
        }
        if(stick==2){
            return m_joystickValues[joy].second;
        }
    }
    return vec2(0,0);
}

bool InputHandler::getButtonState(int joy,int buttonNumber){
    return m_buttonStates[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int buttonNumber){
    return m_mouseButtonStates[buttonNumber];
}

ivec2 InputHandler::getMousePosition(){
    return m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
    if(m_keyStates!=nullptr){
        return m_keyStates[key]==1;
    }
    return false;
}