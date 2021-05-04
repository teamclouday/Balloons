#include "particle.hpp"

void ParticleBullet::update()
{
    auto iter = data.begin();
    while(iter != data.end())
    {
        iter->timeout--;
        if(iter->timeout < 0)
            iter = data.erase(iter);
        else
            iter++;
    }
}

void ParticleBullet::addBullet(glm::vec3& position, int timeout)
{
    data.push_back({position, timeout});
    while(data.size() > MaxBullets)
        data.erase(data.begin());
}