#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public ShooterObject
{
private:
    enum button_state {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    int m_callbackID;
    bool m_released;

public:
    MenuButton();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const& params);

    void setCallback(void (*m_callback)());

    int getCallbackID();
};

class MenuButtonCreator : public BaseCreator {
public:
    GameObject* createGameObject() const {
        return new MenuButton();
    }
};