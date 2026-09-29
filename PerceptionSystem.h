#pragma once

class Enemy;
class Player;
class RaycastSystem;

class PerceptionSystem
{
public:
    bool IsPlayerInRange(
        Enemy& enemy,
        Player& player,
        float detectionRange
    );
    bool IsPlayerInFOV(
        Enemy& enemy,
        Player& player,
        float fovThreshold
    );
    bool CanDetectPlayer(
        Enemy& enemy,
        Player& player,
        RaycastSystem& raycastSystem,
        float detectionRange,
        float fovThreshold
    );
    bool HasLineOfSight(
        Enemy& enemy,
        Player& player,
        RaycastSystem& raycastSystem
    );
};

