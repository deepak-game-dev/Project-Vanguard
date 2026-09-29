#include "Player.h" 

void Player::Update(float dt)
{
}

Vector3 Player::GetPosition() const
{
	return movement.position;
}

Vector3 Player::GetVelocity() const
{
	return movement.velocity;
}

float Player::GetSpeed() const
{
	return movement.speed;
}

float Player::GetAcceleration() const
{
	return movement.acceleration;
}

float Player::GetGravity() const
{
	return gravity;
}

float Player::GetCollisionRadius() const
{
	return collisionRadius;
}

bool Player::IsGrounded() const
{
	return isGrounded;
}

float Player::GetJumpVelocity() const
{
	return jumpVelocity;
}

void Player::SetPosition(const Vector3& newPosition)
{
	movement.position = newPosition;
}

void Player::SetVelocity(const Vector3& newVelocity)
{
	movement.velocity = newVelocity;
}

void Player::SetGrounded(bool grounded)
{
	isGrounded = grounded;
}

MovementData& Player::GetMovementData()
{
	return movement;
}

HealthData& Player::GetHealthData()
{
	return health;
}

bool Player::IsAlive() const
{
	return health.currentHealth > 0.0f;
}
