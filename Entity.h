
#pragma once

class Entity
{
public:
    virtual void Update(float dt) = 0;
    virtual bool IsAlive() const = 0;

    virtual ~Entity() = default;
};