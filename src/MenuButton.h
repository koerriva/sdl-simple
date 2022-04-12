#pragma once

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
private:
    enum button_state {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    bool m_released;

public:
    MenuButton(const LoaderParams* params,void (*m_callback)());

    virtual void draw();
    virtual void update();
    virtual void clean();
};