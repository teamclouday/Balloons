#include "camera.hpp"

Camera::Camera()
{
    pos = glm::vec3(0.0f);
    dir = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUP = glm::vec3(0.0f, 1.0f, 0.0f);
    update();
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
    pos = position;
    dir = glm::normalize(direction);
    worldUP = glm::normalize(up);
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
    glm::vec3 right = glm::normalize(glm::cross(dir, worldUP));
    up = glm::normalize(glm::cross(right, dir));
}