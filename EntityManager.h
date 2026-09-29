#pragma once

#include "Entity.h"
#include <vector>
#include <memory>

class Player;
class Enemy;

class EntityManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void AddEntity(std::unique_ptr<Entity> entity);

    void Update(float dt);

    Player* GetPlayer();
    Enemy* GetEnemy();

    void RemoveDeadEntities();
};