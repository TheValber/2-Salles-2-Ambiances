// FPSCamera.hpp

#pragma once

#include <glimac/glm.hpp>

#include "Room.hpp"

class FPSCamera
{
public:
    FPSCamera(float speed = 0.1f, float sensitivity = 0.1f, float playerRadius = 0.3f);

    void moveFront(float dir, const Room &room);
    void moveRight(float dir, const Room &room);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;

    glm::vec3 getPosition() const;

private:
    float _posX;
    float _posY;
    float _yaw;
    float _pitch;

    float _speed;
    float _sensitivity;

    float _playerRadius;
};
