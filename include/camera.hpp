#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up);
    void update();

    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 worldUP;
    float pitch = 0.0f; // pitch in degree
    float yaw = -90.0f; // yaw in degree
    float rotVel = 1.0f; // rotate velocity
};