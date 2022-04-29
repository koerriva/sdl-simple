#pragma once
#include "GameState.h"
#include <string>

class BetweenLevelState : public GameState
{
private:
    static const std::string s_id;
public:
    BetweenLevelState();
    ~BetweenLevelState();

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_id;}
};
