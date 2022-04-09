#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

using namespace glm;

enum mouse_button {
    LEFT=0,
    MIDDLE=1,
    RIGHT=2
};

class InputHandler
{
private:
    static InputHandler* s_Instance;

    InputHandler();
    ~InputHandler(){};

    std::vector<SDL_Joystick*> m_joysticks;
    bool m_joysticksInitialised = false;
    std::vector<std::pair<vec2,vec2>> m_joystickValues;
    const int m_joystickDeadZone = 10000;
    std::vector<std::vector<bool>> m_buttonStates;

    std::vector<bool> m_mouseButtonStates;

    ivec2 m_mousePosition;
    const Uint8* m_keyStates;

    //keybord
    void onKeyDown(SDL_Event& event);
    void onKeyUp(SDL_Event& event);

    //mouse
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    //joystick
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);
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

    vec2 axis(int joy,int stick);

    bool getButtonState(int joy,int buttonNumber);

    bool getMouseButtonState(int buttonNumber);

    ivec2 getMousePosition();

    bool isKeyDown(SDL_Scancode key);
};
