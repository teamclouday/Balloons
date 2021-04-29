#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    void update();
    void changeView(int deltaX, int deltaY);

    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 worldUP;
    float pitch = 0.0f; // pitch in degree
    float yaw = -90.0f; // yaw in degree
    float rotVel = 1.0f; // rotate velocity
};