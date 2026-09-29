#include "CameraSystem.h"
#include "Player.h"
#include <cmath>
#include <Windows.h>

void CameraSystem::UpdateMouse()
{
    static POINT previousMousePosition;
    static bool firstFrame = true;

    POINT currentMousePosition;

    GetCursorPos(&currentMousePosition);

    if (firstFrame)
    {
        previousMousePosition = currentMousePosition;
        firstFrame = false;
        return;
    }

    float mouseX = static_cast<float>(
        currentMousePosition.x - previousMousePosition.x
        );

    float mouseY = static_cast<float>(
        currentMousePosition.y - previousMousePosition.y
        );

    previousMousePosition = currentMousePosition;

    yaw += mouseX * 0.1f;
    pitch -= mouseY * 0.1f;
}

void CameraSystem::Update(Player& player)
{
    if (pitch > 80.0f)
    {
        pitch = 80.0f;
    }
    else if (pitch < -80.0f)
    {
        pitch = -80.0f;
    }

    float radians = yaw * 3.14159265f / 180.0f;
    float pitchRadians = pitch * 3.14159265f / 180.0f;

    
    float distance = 6.0f;

    float x = std::sin(radians) * std::cos(pitchRadians) * distance;
    float y = std::sin(pitchRadians) * distance;
    float z = -std::cos(radians) * std::cos(pitchRadians) * distance;

    position = player.GetPosition() + Vector3(x, y, z);

    forward = player.GetPosition() - position;

    if (forward.Magnitude() > 0.0f)
    {
        forward = forward.Normalized();
    }
}

Vector3 CameraSystem::GetPosition() const
{
    return position;
}

Vector3 CameraSystem::GetForward() const
{
    return forward;
}

float CameraSystem::GetYaw() const
{
    return yaw;
}

float CameraSystem::GetPitch() const
{
    return pitch;
}
