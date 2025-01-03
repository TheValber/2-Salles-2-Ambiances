// FPSCamera.cpp

#include "../include/FPSCamera.hpp"

FPSCamera::FPSCamera(float speed, float sensitivity, float playerRadius)
    : _posX(0.f), _posY(0.f), _yaw(0.f), _pitch(0.f), _speed(speed), _sensitivity(sensitivity), _playerRadius(playerRadius)
{
}

void FPSCamera::moveFront(float dir, const Room &room)
{
    auto newPosX = _posX + dir * glm::cos(glm::radians(_yaw)) * _speed;
    auto newPosY = _posY + dir * glm::sin(glm::radians(_yaw)) * _speed;

    if (room.isInWall(glm::vec3(newPosX, 2.f, newPosY), _playerRadius))
    {
        if (!room.isInWall(glm::vec3(newPosX, 2.f, _posY), _playerRadius))
        {
            _posX = newPosX;
        }
        else if (!room.isInWall(glm::vec3(_posX, 2.f, newPosY), _playerRadius))
        {
            _posY = newPosY;
        }
        return;
    }

    _posX = newPosX;
    _posY = newPosY;
}

void FPSCamera::moveRight(float dir, const Room &room)
{
    auto newPosX = _posX + dir * glm::cos(glm::radians(_yaw + 90)) * _speed;
    auto newPosY = _posY + dir * glm::sin(glm::radians(_yaw + 90)) * _speed;

    if (room.isInWall(glm::vec3(newPosX, 2.f, newPosY), _playerRadius))
    {
        if (!room.isInWall(glm::vec3(newPosX, 2.f, _posY), _playerRadius))
        {
            _posX = newPosX;
        }
        else if (!room.isInWall(glm::vec3(_posX, 2.f, newPosY), _playerRadius))
        {
            _posY = newPosY;
        }
        return;
    }

    _posX = newPosX;
    _posY = newPosY;
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

glm::vec3 FPSCamera::getPosition() const
{
    return glm::vec3(_posX, 2.f, _posY);
}
