// FPSCamera.cpp

#include "../include/FPSCamera.hpp"

FPSCamera::FPSCamera(float speed, float sensitivity)
    : _posX(0.f), _posY(0.f), _yaw(0.f), _pitch(0.f), _speed(speed), _sensitivity(sensitivity)
{
}

void FPSCamera::moveFront(float dir)
{
    _posX += dir * glm::cos(glm::radians(_yaw)) * _speed;
    _posY += dir * glm::sin(glm::radians(_yaw)) * _speed;
}

void FPSCamera::moveRight(float dir)
{
    _posX += dir * glm::cos(glm::radians(_yaw + 90)) * _speed;
    _posY += dir * glm::sin(glm::radians(_yaw + 90)) * _speed;
}

void FPSCamera::rotateLeft(float degrees)
{
    _yaw += degrees * _sensitivity;
}

void FPSCamera::rotateUp(float degrees)
{
    _pitch += degrees * _sensitivity;
    if (_pitch > 89.f)
    {
        _pitch = 89.f;
    }
    if (_pitch < -89.f)
    {
        _pitch = -89.f;
    }
}

glm::mat4 FPSCamera::getViewMatrix() const
{
    glm::vec3 position = glm::vec3(_posX, 2.f, _posY);

    glm::vec3 direction = glm::normalize(glm::vec3(glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch)),
                                                   glm::sin(glm::radians(_pitch)),
                                                   glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch))));

    glm::vec3 worldUp = glm::vec3(0, 1, 0);
    glm::vec3 left = glm::normalize(glm::cross(worldUp, direction));
    glm::vec3 up = glm::cross(direction, left);

    return glm::lookAt(position, position + direction, up);
}
