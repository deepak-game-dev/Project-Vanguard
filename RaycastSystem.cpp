#include "RaycastSystem.h"
#include "Player.h"
#include "Vector3.h"
#include <cmath>

bool RaycastSystem::CheckGround(Player& player, float rayLength)
{
    float playerY = player.GetPosition().y;
    if (playerY <= rayLength)
    {
        return true;
    }
    return false;
}

bool RaycastSystem::CheckRayHit(
    const Vector3& start,
    const Vector3& direction,
    float rayLength)
{
    Vector3 obstaclePosition(5.0f, 0.0f, 5.0f);
    float obstacleRadius = 1.0f;

    Vector3 toObstacle =
        obstaclePosition - start;

    float distanceAlongRay =
        toObstacle.x * direction.x +
        toObstacle.y * direction.y +
        toObstacle.z * direction.z;

    if (distanceAlongRay < 0.0f ||
        distanceAlongRay > rayLength)
    {
        return false;
    }

    Vector3 closestPoint =
        start + direction * distanceAlongRay;

    Vector3 difference =
        obstaclePosition - closestPoint;

    float distanceFromRay =
        difference.Magnitude();

    if (distanceFromRay <= obstacleRadius)
        return true;

    return false;
}
