#include "HealthSystem.h"

void HealthSystem::TakeDamage(
    HealthData& health,
    float damage)
{
    if (damage <= 0.0f)
        return;

    health.currentHealth -= damage;

    if (health.currentHealth < 0.0f)
    {
        health.currentHealth = 0.0f;
    }
}

void HealthSystem::Heal(
    HealthData& health,
    float amount)
{
    if (amount <= 0.0f)
        return;

    health.currentHealth += amount;

    if (health.currentHealth > health.maxHealth)
    {
        health.currentHealth = health.maxHealth;
    }
}

bool HealthSystem::IsDead(const HealthData& health)
{
    return health.currentHealth <= 0.0f;
}
