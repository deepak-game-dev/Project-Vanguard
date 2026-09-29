#pragma once

class Player;
class Vector3;

class RaycastSystem
{
public:
    bool CheckGround(Player& player, float rayLength);
    bool CheckRayHit(
        const Vector3& start,
        const Vector3& direction,
        float rayLength
    );
};

