#include "PlayState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

}

void PlayState::render(){

}

bool PlayState::onEnter(){
    std::cout << "entring PlayState" << std::endl;
    return true;
}

bool PlayState::onExit(){
    std::cout << "exiting PlayState" << std::endl;
    return true;
}