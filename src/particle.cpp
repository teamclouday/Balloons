#include "particle.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <cstdlib>

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
    float degree = 0.0f; // angle on XZ plane
    for(int i = 0; i < num; i++)
    {
        float x = std::cos(glm::radians(degree));
        float z = std::sin(glm::radians(degree));
        float y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 10.0f; // range: 0.0 to 10.0
        particles.push_back(new Particle{
            // center + glm::vec3(x, 0.0f, z) * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 0.5f * radius,
            center,
            glm::normalize(glm::vec3(x, y, z)) * radius
        });
        degree += (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 20.0f + 10.0f); // range: 10.0 to 30.0f
    }
    // reference: https://stackoverflow.com/questions/43044/algorithm-to-randomly-generate-an-aesthetically-pleasing-color-palette
    const glm::vec3 mixedColor{1.0f, 1.0f, 0.1f}; // bright yellow
    color = glm::vec3(
        (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) + mixedColor.r) / 2.0f,
        (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) + mixedColor.g) / 2.0f,
        (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) + mixedColor.b) / 2.0f
    );
}

Firework::~Firework()
{
    for(auto& p : particles) delete p;
}

void Firework::update(int fps)
{
    timeout--;
    float deltaTime = 1.0f / fps;
    // the only force to consider is the gravity
    glm::vec3 deltaVel{0.0f, -GRAVITY_G * deltaTime, 0.0f};
    for(auto& p : particles)
    {
        p->vel += deltaVel;
        p->pos += p->vel * deltaTime;
    }
}