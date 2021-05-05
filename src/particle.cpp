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

void ParticleBalloon::loadBalloonsBegin()
{

}

void ParticleBalloon::loadBalloonsStage1()
{

}

void ParticleBalloon::loadBalloonsStage2()
{

}

void ParticleBalloon::loadBalloonsStage3()
{

}

void ParticleBalloon::loadBalloonsStage4()
{

}

void ParticleBalloon::update(int fps)
{

}

Firework::Firework(int num, int timeout, float radius, glm::vec3 center)
{
    this->timeout = timeout;

}

void Firework::update(int fps)
{
    timeout--;
    float deltaTime = 1.0f / fps;
    // the only force to consider is the gravity
    glm::vec3 deltaVel{0.0f, GRAVITY_G * deltaTime, 0.0f};
    for(auto& p : particles)
    {
        p.vel += deltaVel;
        p.pos += p.vel * deltaTime;
    }
}