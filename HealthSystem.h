#pragma once

#include "HealthData.h"

class HealthSystem
{
public:
    void TakeDamage(HealthData& health, float damage);
    void Heal(HealthData& health, float amount);
    bool IsDead(const HealthData& health);
};
