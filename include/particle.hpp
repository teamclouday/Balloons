// This header defines particle systems for different objects
#pragma once

#include <glm/glm.hpp>
#include <vector>

// This class defines the bullets left on the objects
class ParticleBullet
{
public:
    void update();
    void addBullet(glm::vec3& position, int timeout);

    const int MaxBullets = 15;
    struct BulletData
    {
        glm::vec3 pos;
        int timeout;
    };
    std::vector<BulletData> data;
};