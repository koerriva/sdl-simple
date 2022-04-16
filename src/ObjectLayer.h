#pragma once

#include "Layer.h"
#include "GameObject.h"

#include <vector>

class Player;
class Enemy;

class ObjectLayer : public Layer
{
private:
    std::vector<GameObject*> m_gameObjects;
    Player* m_player = nullptr;
    std::vector<Enemy*> m_enemies;
public:
    ObjectLayer(){};
    ~ObjectLayer(){};

    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects(){
        return &m_gameObjects;
    }

    void setPlayer(GameObject* player){
        m_player = (Player*)player;
    }

    void addEnemy(GameObject* enemy){
        auto ptr = (Enemy*)enemy;
        m_enemies.push_back(ptr);
    }

    Player* getPlayer() const {return m_player;}
    std::vector<Enemy*> getEnemies() const {return m_enemies;}
};
