#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* state){
    m_gameStates.push_back(state);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* state){
    if(!m_gameStates.empty()){
        //remove old state
        if(m_gameStates.back()->getStateID() == state->getStateID()){
            return;
        }

        if(m_gameStates.back()->onExit()){
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }

    //push new state
    m_gameStates.push_back(state);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState(){
    if(!m_gameStates.empty()){
        if(m_gameStates.back()->onExit()){
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::update(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->render();
    }
}