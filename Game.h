#pragma once
#include "EntityManager.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "RaycastSystem.h"
#include "CameraSystem.h"
#include "AiSystem.h"
#include "HealthSystem.h"	
#include "PerceptionSystem.h"

class Game
{
private:
	EntityManager entityManager;
	InputSystem inputSystem;
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	RaycastSystem raycastSystem;
	CameraSystem cameraSystem;
	AISystem aiSystem;
	HealthSystem healthSystem;
	PerceptionSystem perceptionSystem;

public:
	void Run();
};
