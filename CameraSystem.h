#pragma once

#include "Vector3.h"

class Player;

class CameraSystem
{
private:
    Vector3 position;
    Vector3 forward;

    float yaw = 0.0f;
    float pitch = 20.0f;

public:
    void Update(Player& player);
    void UpdateMouse();

    Vector3 GetPosition() const;
    Vector3 GetForward() const;

    float GetYaw() const;
    float GetPitch() const;
};

