#pragma once 
#include "Entity.h" 
#include "Vector3.h" 
#include "MovementData.h" 
#include "HealthData.h" 

class Player : public Entity
{
private:
	MovementData movement;
	float gravity = -9.8f;
	bool isGrounded = true;
	float jumpVelocity = 10.0f;
	float collisionRadius = 0.5f;
	HealthData health{ 100.0f, 100.0f };

public:
	void Update(float dt) override;
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;
	float GetSpeed() const;
	void SetPosition(const Vector3& newposition);
	void SetVelocity(const Vector3& newvelocity);
	float GetAcceleration() const;
	float GetGravity() const;
	bool IsGrounded() const;
	float GetJumpVelocity() const;
	float GetCollisionRadius() const;
	void SetGrounded(bool grounded);
	MovementData& GetMovementData();
	HealthData& GetHealthData();
	bool IsAlive() const override;
};
