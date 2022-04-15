#include "Level.h"

void Level::update(){
    for(auto const layer : m_layers){
        layer->update();
    }
}

void Level::render(){
    for(auto const layer : m_layers){
        layer->render();
    }
}