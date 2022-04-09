#pragma once

#include <vector>
#include <SDL2/SDL.h>

class InputHandler
{
private:
    static InputHandler* s_Instance;

    InputHandler(){};
    ~InputHandler(){};

    std::vector<SDL_Joystick*> m_joysticks;
    bool m_joysticksInitialised = false;
public:
    static InputHandler* Instance(){
        if(s_Instance==nullptr){
            s_Instance = new InputHandler();
        }
        return s_Instance;
    }

    void update();
    void clean();

    void initialiseJoysticks();
    bool joysticksInitialised() const {
        return m_joysticksInitialised;
    };
};
