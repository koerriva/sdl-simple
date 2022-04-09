#include "InputHandler.h"
#include <iostream>
#include "Game.h"

InputHandler* InputHandler::s_Instance = nullptr;

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
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            Game::Instance()->quit();
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