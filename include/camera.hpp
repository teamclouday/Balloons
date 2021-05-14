// camera.hpp
// Assignment: CIS425 Final Project
// Environment/Compiler:
//                  Visual Studio Community 2019 (Tested)
//                  Linux GCC (Tested)
//                  MacOS GCC (Not Tested)
// Date: May 14, 2021
// Official Name:  Sida Zhu
// E-mail:
//      szhu28@syr.edu
//      teamclouday@gmail.com
// File Description:
//      This header file declares Camera class for first person view
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
    glm::vec3 right;
    glm::vec3 worldUP;
    float pitch = 0.0f; // pitch in degree
    float yaw = -90.0f; // yaw in degree
    float rotVel = 1.0f; // rotate velocity
};