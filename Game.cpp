#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "AiSystem.h"
#include <chrono>
#include <iostream>

void Game::Run()
{
    bool gameRunning = true;

    entityManager.AddEntity(std::make_unique<Player>());
    entityManager.AddEntity(std::make_unique<Enemy>());

    Player* player = entityManager.GetPlayer();
    Enemy* enemy = entityManager.GetEnemy();

    if (player != nullptr)
    {
        player->SetPosition(
            Vector3(0.0f, 0.0f, 3.0f)
        );
    }

    if (enemy != nullptr)
    {
        enemy->SetPosition(
            Vector3(0.0f, 0.0f, 0.0f)
        );
    }

    auto previousTime =
        std::chrono::high_resolution_clock::now();

    while (gameRunning)
    {
        auto currentTime =
            std::chrono::high_resolution_clock::now();

        float dt =
            std::chrono::duration<float>(
                currentTime - previousTime
            ).count();

        previousTime = currentTime;

        inputSystem.Update();
        cameraSystem.UpdateMouse();

        player = entityManager.GetPlayer();
        enemy = entityManager.GetEnemy();

        if (player != nullptr)
        {
            Vector3 playerDirection(0.0f, 0.0f, 0.0f);

            if (inputSystem.IsHeld(Action::MoveForward))
                playerDirection.z += 1.0f;

            if (inputSystem.IsHeld(Action::MoveBackward))
                playerDirection.z -= 1.0f;

            if (inputSystem.IsHeld(Action::MoveLeft))
                playerDirection.x -= 1.0f;

            if (inputSystem.IsHeld(Action::MoveRight))
                playerDirection.x += 1.0f;

            movementSystem.Update(
                player->GetMovementData(),
                playerDirection,
                dt
            );

            bool grounded =
                raycastSystem.CheckGround(
                    *player,
                    0.6f
                );

            player->SetGrounded(grounded);
            cameraSystem.Update(*player);
        }

        if (player != nullptr && enemy != nullptr)
        {
            if (inputSystem.IsPressed(Action::Attack))
            {
                float distance =
                    (
                        enemy->GetPosition() -
                        player->GetPosition()
                        ).Magnitude();

                if (distance <= 2.0f)
                {
                    healthSystem.TakeDamage(
                        enemy->GetHealthData(),
                        20.0f
                    );

                    std::cout
                        << "Enemy Health: "
                        << enemy->GetHealthData().currentHealth
                        << std::endl;
                }
            }
        }

        if (player != nullptr && enemy != nullptr)
        {
            aiSystem.UpdateState(
                *enemy,
                *player,
                perceptionSystem,
                raycastSystem
            );

            aiSystem.UpdateAttackTimer(
                *enemy,
                dt
            );

            if (enemy->GetState() == EnemyState::Investigate)
            {
                aiSystem.UpdateInvestigationTimer(
                    *enemy,
                    dt
                );
            }

            if (enemy->GetState() == EnemyState::Attack)
            {
                aiSystem.Attack(
                    *enemy,
                    *player,
                    healthSystem
                );
            }

            Vector3 enemyDirection =
                aiSystem.GetMovementDirection(
                    *enemy,
                    *player
                );

            if (enemyDirection.Magnitude() > 0.0f)
            {
                enemy->SetForward(enemyDirection);
            }

            movementSystem.Update(
                enemy->GetMovementData(),
                enemyDirection,
                dt
            );

            collisionSystem.Update(*enemy);
        }

        if (player != nullptr)
        {
            collisionSystem.Update(*player);
        }

        entityManager.Update(dt);
        entityManager.RemoveDeadEntities();

        if (player != nullptr && healthSystem.IsDead(player->GetHealthData()))
        {
            std::cout << "GAME OVER" << std::endl;
            gameRunning = false;
        }
    }
}
