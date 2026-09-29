#pragma once 
#include "Entity.h" 
#include "Vector3.h" 
#include "MovementData.h" 
#include "HealthData.h" 
#include "EnemyState.h" 

class Enemy : public Entity
{
private:
	MovementData movement;
	float collisionRadius = 0.5f;
	HealthData health{ 100.0f, 100.0f };
	Vector3 forward{ 0.0f, 0.0f, 1.0f };
	EnemyState state = EnemyState::Patrol;
	Vector3 lastKnownPlayerPosition;
	float stateTimer = 0.0f;
	float attackDamage = 10.0f;
	float attackCooldown = 1.0f;
	float attackTimer = 0.0f;
	Vector3 patrolPointA{ 0.0f, 0.0f, 0.0f };
	Vector3 patrolPointB{ 10.0f, 0.0f, 0.0f };
	bool movingToPointB = true;
	

public:
	void Update(float dt) override;
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;
	float GetSpeed() const;
	float GetAcceleration() const;
	void SetPosition(const Vector3& newPosition);
	void SetVelocity(const Vector3& newVelocity);
	MovementData& GetMovementData();
	HealthData& GetHealthData();
	float GetCollisionRadius() const;
	Vector3 GetForward() const;
	EnemyState GetState() const;
	void SetState(EnemyState newState);
	Vector3 GetLastKnownPlayerPosition() const;
	void SetLastKnownPlayerPosition(const Vector3& position);
	float GetStateTimer() const;
	void SetStateTimer(float time);
	float GetAttackDamage() const;
	float GetAttackCooldown() const;
	float GetAttackTimer() const;
	void SetAttackTimer(float time);
	bool IsDead() const;
	bool IsAlive() const override;
	Vector3 GetPatrolPointA() const;
	Vector3 GetPatrolPointB() const;
	bool IsMovingToPointB() const;
	void SetMovingToPointB(bool value);
	void SetForward(const Vector3& newForward);
};
