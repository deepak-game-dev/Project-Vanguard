#include "AISystem.h"
#include "Enemy.h"
#include "Player.h"
#include "Vector3.h"
#include "PerceptionSystem.h"
#include "RaycastSystem.h"
#include "HealthSystem.h"

Vector3 AISystem::GetDirectionToPlayer(
    Enemy& enemy,
    Player& player)
{
    Vector3 direction =
        player.GetPosition() -
        enemy.GetPosition();

    if (direction.Magnitude() > 0.0f)
    {
        direction = direction.Normalized();
    }

    return direction;
}

EnemyState AISystem::GetState(Enemy& enemy)
{
    return enemy.GetState();
}

void AISystem::SetState(
    Enemy& enemy,
    EnemyState newState)
{
    enemy.SetState(newState);
}

void AISystem::UpdateState(
    Enemy& enemy,
    Player& player,
    PerceptionSystem& perceptionSystem,
    RaycastSystem& raycastSystem)
{
    bool canDetectPlayer =
        perceptionSystem.CanDetectPlayer(
            enemy,
            player,
            raycastSystem,
            10.0f,
            0.5f
        );

    float distance =
        (
            player.GetPosition() -
            enemy.GetPosition()
            ).Magnitude();

    EnemyState state = GetState(enemy);

    switch (state)
    {
    case EnemyState::Patrol:
        if (canDetectPlayer)
        {
            enemy.SetLastKnownPlayerPosition(
                player.GetPosition()
            );

            SetState(
                enemy,
                EnemyState::Chase
            );
        }
        break;

    case EnemyState::Chase:
        if (canDetectPlayer)
        {
            enemy.SetLastKnownPlayerPosition(
                player.GetPosition()
            );

            if (distance <= 2.0f)
            {
                SetState(
                    enemy,
                    EnemyState::Attack
                );
            }
        }
        else
        {
            SetState(
                enemy,
                EnemyState::Investigate
            );

            enemy.SetStateTimer(5.0f);
        }
        break;

    case EnemyState::Attack:
        if (!canDetectPlayer)
        {
            SetState(
                enemy,
                EnemyState::Investigate
            );

            enemy.SetStateTimer(5.0f);
        }
        else if (distance > 2.0f)
        {
            SetState(
                enemy,
                EnemyState::Chase
            );
        }
        break;

    case EnemyState::Investigate:
        if (canDetectPlayer)
        {
            enemy.SetLastKnownPlayerPosition(
                player.GetPosition()
            );

            SetState(
                enemy,
                EnemyState::Chase
            );
        }
        break;
    }
}

Vector3 AISystem::GetMovementDirection(
    Enemy& enemy,
    Player& player)
{
    switch (GetState(enemy))
    {
    case EnemyState::Patrol:
    {
        Vector3 target;

        if (enemy.IsMovingToPointB())
        {
            target = enemy.GetPatrolPointB();
        }
        else
        {
            target = enemy.GetPatrolPointA();
        }

        Vector3 direction =
            target - enemy.GetPosition();

        if (direction.Magnitude() < 0.2f)
        {
            enemy.SetMovingToPointB(
                !enemy.IsMovingToPointB()
            );

            return Vector3(
                0.0f,
                0.0f,
                0.0f
            );
        }

        return direction.Normalized();
    }

    case EnemyState::Chase:
        return GetDirectionToPlayer(
            enemy,
            player
        );

    case EnemyState::Attack:
        return Vector3(
            0.0f,
            0.0f,
            0.0f
        );

    case EnemyState::Investigate:
    {
        Vector3 direction =
            enemy.GetLastKnownPlayerPosition()
            - enemy.GetPosition();

        if (direction.Magnitude() > 0.1f)
        {
            return direction.Normalized();
        }

        return Vector3(
            0.0f,
            0.0f,
            0.0f
        );
    }
    }

    return Vector3(
        0.0f,
        0.0f,
        0.0f
    );
}

void AISystem::UpdateInvestigationTimer(
    Enemy& enemy,
    float dt)
{
    float timer = enemy.GetStateTimer();
    timer -= dt;

    if (timer < 0.0f)
    {
        timer = 0.0f;
    }

    enemy.SetStateTimer(timer);

    if (timer <= 0.0f)
    {
        SetState(
            enemy,
            EnemyState::Patrol
        );
    }
}

void AISystem::Attack(
    Enemy& enemy,
    Player& player,
    HealthSystem& healthSystem)
{
    if (enemy.GetAttackTimer() > 0.0f)
    {
        return;
    }

    healthSystem.TakeDamage(
        player.GetHealthData(),
        enemy.GetAttackDamage()
    );

    enemy.SetAttackTimer(
        enemy.GetAttackCooldown()
    );
}

void AISystem::UpdateAttackTimer(
    Enemy& enemy,
    float dt)
{
    float timer = enemy.GetAttackTimer();

    if (timer > 0.0f)
    {
        timer -= dt;

        if (timer < 0.0f)
        {
            timer = 0.0f;
        }

        enemy.SetAttackTimer(timer);
    }
}

