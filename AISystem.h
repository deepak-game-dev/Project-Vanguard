#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Vector3.h"
#include "PerceptionSystem.h"
#include "RaycastSystem.h"
#include "HealthSystem.h"

class AISystem
{
public:
    Vector3 GetDirectionToPlayer(Enemy& enemy, Player& player);
    EnemyState GetState(Enemy& enemy);


    void SetState(Enemy& enemy, EnemyState newState);

    void UpdateState(
        Enemy& enemy,
        Player& player,
        PerceptionSystem& perceptionSystem,
        RaycastSystem& raycastSystem
    );

    Vector3 GetMovementDirection(Enemy& enemy, Player& player);


    void UpdateInvestigationTimer(Enemy& enemy, float dt);
    void Attack(Enemy& enemy, Player& player, HealthSystem& healthSystem);
    void UpdateAttackTimer(Enemy& enemy, float dt);
};
