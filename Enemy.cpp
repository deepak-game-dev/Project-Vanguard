#include "Enemy.h"

void Enemy::Update(float dt)
{
}

Vector3 Enemy::GetPosition() const
{
	return movement.position;
}

Vector3 Enemy::GetVelocity() const
{
	return movement.velocity;
}

float Enemy::GetSpeed() const
{
	return movement.speed;
}

float Enemy::GetAcceleration() const
{
	return movement.acceleration;
}

void Enemy::SetPosition(const Vector3& newPosition)
{
	movement.position = newPosition;
}

void Enemy::SetVelocity(const Vector3& newVelocity)
{
	movement.velocity = newVelocity;
}

MovementData& Enemy::GetMovementData()
{
	return movement;
}

float Enemy::GetCollisionRadius() const
{
	return collisionRadius;
}

HealthData& Enemy::GetHealthData()
{
	return health;
}

Vector3 Enemy::GetForward() const
{
	return forward;
}

EnemyState Enemy::GetState() const
{
	return state;
}

void Enemy::SetState(EnemyState newState)
{
	state = newState;
}

Vector3 Enemy::GetLastKnownPlayerPosition() const
{
	return lastKnownPlayerPosition;
}

void Enemy::SetLastKnownPlayerPosition(const Vector3& position)
{
	lastKnownPlayerPosition = position;
}

float Enemy::GetStateTimer() const
{
	return stateTimer;
}

void Enemy::SetStateTimer(float time)
{
	stateTimer = time;
}

float Enemy::GetAttackDamage() const
{
	return attackDamage;
}

float Enemy::GetAttackCooldown() const
{
	return attackCooldown;
}

float Enemy::GetAttackTimer() const
{
	return attackTimer;
}

void Enemy::SetAttackTimer(float time)
{
	attackTimer = time;
}

bool Enemy::IsDead() const
{
	return health.currentHealth <= 0.0f;
}

bool Enemy::IsAlive() const
{
	return health.currentHealth > 0.0f;
}

Vector3 Enemy::GetPatrolPointA() const
{
	return patrolPointA;
}

Vector3 Enemy::GetPatrolPointB() const
{
	return patrolPointB;
}

bool Enemy::IsMovingToPointB() const
{
	return movingToPointB;
}

void Enemy::SetMovingToPointB(bool value)
{
	movingToPointB = value;
}
void Enemy::SetForward(
	const Vector3& newForward)
{
	if (newForward.Magnitude() > 0.0f)
	{
		forward =
			newForward.Normalized();
	}
}
