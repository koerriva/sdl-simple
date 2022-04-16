#include "ObjectLayer.h"

void ObjectLayer::update(){
    for (auto const o : m_gameObjects)
    {
        o->update();
    }
}

void ObjectLayer::render(){
    for (auto const o : m_gameObjects)
    {
        o->draw();
    }
}