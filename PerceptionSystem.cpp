#include "PerceptionSystem.h"
#include "Enemy.h"
#include "Player.h"
#include "Vector3.h"
#include "RaycastSystem.h"

bool PerceptionSystem::IsPlayerInRange(
    Enemy& enemy,
    Player& player,
    float detectionRange)
{
    Vector3 direction =
        player.GetPosition() - enemy.GetPosition();

    float distance = direction.Magnitude();

    return distance <= detectionRange;
}

bool PerceptionSystem::IsPlayerInFOV(
    Enemy& enemy,
    Player& player,
    float fovThreshold)
{
    Vector3 direction =
        player.GetPosition() - enemy.GetPosition();

    if (direction.Magnitude() == 0.0f)
    {
        return true;
    }

    direction = direction.Normalized();

    Vector3 forward = enemy.GetForward();

    float dot =
        forward.x * direction.x +
        forward.y * direction.y +
        forward.z * direction.z;

    return dot >= fovThreshold;
}

bool PerceptionSystem::CanDetectPlayer(
    Enemy& enemy,
    Player& player,
    RaycastSystem& raycastSystem,
    float detectionRange,
    float fovThreshold)
{
    if (!IsPlayerInRange(enemy, player, detectionRange))
        return false;

    if (!IsPlayerInFOV(enemy, player, fovThreshold))
        return false;

    if (!HasLineOfSight(enemy, player, raycastSystem))
        return false;

    return true;
}

bool PerceptionSystem::HasLineOfSight(
    Enemy& enemy,
    Player& player,
    RaycastSystem& raycastSystem)
{
    Vector3 direction =
        player.GetPosition() - enemy.GetPosition();

    if (direction.Magnitude() == 0.0f)
    {
        return true;
    }

    direction = direction.Normalized();

    float distance =
        (player.GetPosition() - enemy.GetPosition()).Magnitude();

    return !raycastSystem.CheckRayHit(
        enemy.GetPosition(),
        direction,
        distance
    );
}
