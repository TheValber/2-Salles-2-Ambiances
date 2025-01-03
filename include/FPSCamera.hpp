// FPSCamera.hpp

#pragma once

#include <glimac/glm.hpp>

class FPSCamera
{
public:
    FPSCamera(float speed = 0.1f, float sensitivity = 0.1f);

    void moveFront(float dir);
    void moveRight(float dir);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;

private:
    float _posX;
    float _posY;
    float _yaw;
    float _pitch;

    float _speed;
    float _sensitivity;
};
