#include "CollisionSystem.h"
#include "Player.h"
#include "Vector3.h"
#include "Enemy.h"

void CollisionSystem::Update(Player& player)
{
    Vector3 obstaclePosition(
        5.0f,
        0.0f,
        5.0f
    );

    float obstacleRadius = 1.0f;

    Vector3 difference =
        obstaclePosition -
        player.GetPosition();

    float distance =
        difference.Magnitude();

    float combinedRadius =
        player.GetCollisionRadius() +
        obstacleRadius;


    // =====================
    // OBSTACLE COLLISION
    // =====================

    if (distance < combinedRadius)
    {
        Vector3 collisionNormal =
            difference.Normalized();

        float penetration =
            combinedRadius - distance;

        Vector3 correction =
            collisionNormal * penetration;

        Vector3 newPosition =
            player.GetPosition() - correction;

        player.SetPosition(newPosition);


        float velocityIntoSurface =
            player.GetVelocity().x *
            collisionNormal.x +

            player.GetVelocity().y *
            collisionNormal.y +

            player.GetVelocity().z *
            collisionNormal.z;


        if (velocityIntoSurface > 0.0f)
        {
            Vector3 velocity =
                player.GetVelocity();

            velocity =
                velocity -
                collisionNormal *
                velocityIntoSurface;

            player.SetVelocity(velocity);
        }
    }



    if (player.GetPosition().y <= 0.0f)
    {
        Vector3 position =
            player.GetPosition();

        position.y = 0.0f;


        Vector3 velocity =
            player.GetVelocity();

        velocity.y = 0.0f;


        player.SetPosition(position);
        player.SetVelocity(velocity);
    }
}

void CollisionSystem::Update(Enemy& enemy)
{
    Vector3 obstaclePosition(5.0f, 0.0f, 5.0f);
    float obstacleRadius = 1.0f;

    Vector3 difference =
        obstaclePosition - enemy.GetPosition();

    float distance = difference.Magnitude();

    float combinedRadius =
        enemy.GetCollisionRadius() + obstacleRadius;

    if (distance < combinedRadius)
    {
        Vector3 collisionNormal = difference.Normalized();

        float penetration =
            combinedRadius - distance;

        Vector3 correction =
            collisionNormal * penetration;

        Vector3 newPosition =
            enemy.GetPosition() - correction;

        enemy.SetPosition(newPosition);

        float velocityIntoSurface =
            enemy.GetVelocity().x * collisionNormal.x +
            enemy.GetVelocity().y * collisionNormal.y +
            enemy.GetVelocity().z * collisionNormal.z;

        if (velocityIntoSurface > 0.0f)
        {
            Vector3 velocity = enemy.GetVelocity();

            velocity =
                velocity - collisionNormal * velocityIntoSurface;

            enemy.SetVelocity(velocity);
        }
    }

    if (enemy.GetPosition().y <= 0.0f)
    {
        Vector3 position = enemy.GetPosition();
        position.y = 0.0f;

        Vector3 velocity = enemy.GetVelocity();
        velocity.y = 0.0f;

        enemy.SetPosition(position);
        enemy.SetVelocity(velocity);
    }
}
