#include "camera.hpp"
#include <algorithm>

Camera::Camera()
{
    pos = glm::vec3(0.0f);
    dir = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUP = glm::vec3(0.0f, 1.0f, 0.0f);
    update();
}

void Camera::update()
{
    glm::vec3 newdir{
        std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch)),
        std::sin(glm::radians(pitch)),
        std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch))
    };
    dir = glm::normalize(newdir);
    right = glm::normalize(glm::cross(dir, worldUP));
    up = glm::normalize(glm::cross(right, dir));
}

void Camera::changeView(int deltaX, int deltaY)
{
    yaw += deltaX * rotVel;
    pitch -= deltaY * rotVel;
    pitch = std::max(std::min(pitch, 89.0f), -89.0f);
}