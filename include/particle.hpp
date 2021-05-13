// This header defines particle systems for different objects
#pragma once

#include <glm/glm.hpp>
#include <vector>

#define GRAVITY_G 9.8f // m/s^2

// This class defines the bullets left on the objects
class ParticleBullet
{
public:
    void update();
    void addBullet(glm::vec3& position, int timeout);

    const unsigned MaxBullets = 10;
    struct BulletData
    {
        glm::vec3 pos;
        int timeout;
    };
    std::vector<BulletData> data;
};

// This class collects and updates the balloons at every game stage
class ParticleBalloon
{
public:
    enum BallonColor
    {
        RED = 0,
        BLUE = 1,
        GREEN = 2,
        YELLOW = 3,
        PINK = 4,
    };
    // The balloon object structure
    struct Balloon
    {
        BallonColor color;
        glm::vec3 pos;
        glm::vec3 vel; // this is the velocity
        float radius; // the size of the balloon
    };
    std::vector<Balloon> balloons;
    bool enablePhysics = false; // whether to enable physics (gravity, wind)
    bool enableWindForce = false; // whether to enable wind force
    void loadBalloonsTest();
    void loadBalloonsBegin();
    void loadBalloonsStage1();
    void loadBalloonsStage2();
    void loadBalloonsStage3();
    void loadBalloonsStage4();
    void update(int fps); // update positions if enablePhysics
};

// This class is created to show a firework
// either after balloon explodes
// or at the end after winning the game
class Firework
{
public:
    struct Particle
    {
        glm::vec3 pos;
        glm::vec3 vel;
    };
    Firework(int num, int timeout, float radius, glm::vec3 center);
    ~Firework();
    void update(int fps); // update particle positions
    std::vector<Particle*> particles;
    glm::vec3 color; // color is randomly generated
    int timeout;
};