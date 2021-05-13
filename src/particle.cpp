#include "particle.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <cstdlib>
#include <algorithm>

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

void ParticleBalloon::loadBalloonsTest()
{
    // load some balloons to test functions
    enablePhysics = true;
    balloons.push_back({
        BallonColor::RED,
        glm::vec3(0.0f, 25.0f, -100.0f),
        glm::vec3(0.0f, 5.0f, 0.0f),
        8.0f
    });
    balloons.push_back({
        BallonColor::YELLOW,
        glm::vec3(0.0f, 5.0f, -100.0f),
        glm::vec3(0.0f, 2.5f, 0.0f),
        8.0f
    });
}

void ParticleBalloon::loadBalloonsBegin()
{
    // load one balloon on the front wall
    // ask player to shoot
    balloons.clear();
    balloons.resize(0);
    enablePhysics = false;
    const int wallSides = 5;
    // const float wallHeight = 100.0f;
    const float wallWidth = 500.0f;
    float wallAngle = 360.0f / wallSides;
    float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    wallDist *= 0.8f;
    balloons.push_back({
        BallonColor::RED,
        glm::vec3(-wallDist * std::sin(glm::radians(0.0f)), 25.0f, -wallDist * std::cos(glm::radians(0.0f))),
        glm::vec3(0.0f),
        8.0f
    });
    balloons.push_back({
        BallonColor::BLUE,
        glm::vec3(-wallDist * std::sin(glm::radians(wallAngle/4.0f)), 25.0f, -wallDist * std::cos(glm::radians(wallAngle/4.0f))),
        glm::vec3(0.0f),
        8.0f
    });
    balloons.push_back({
        BallonColor::GREEN,
        glm::vec3(-wallDist * std::sin(glm::radians(-wallAngle/4.0f)), 25.0f, -wallDist * std::cos(glm::radians(-wallAngle/4.0f))),
        glm::vec3(0.0f),
        8.0f
    });
    balloons.push_back({
        BallonColor::PINK,
        glm::vec3(-wallDist * std::sin(glm::radians(wallAngle/8.0f)), 0.0f, -wallDist * std::cos(glm::radians(wallAngle/8.0f))),
        glm::vec3(0.0f),
        8.0f
    });
    balloons.push_back({
        BallonColor::YELLOW,
        glm::vec3(-wallDist * std::sin(glm::radians(-wallAngle/8.0f)), 0.0f, -wallDist * std::cos(glm::radians(-wallAngle/8.0f))),
        glm::vec3(0.0f),
        8.0f
    });
}

void ParticleBalloon::loadBalloonsStage1()
{
    // load balloons on every wall
    // ask player to shoot all of them
    balloons.clear();
    balloons.resize(0);
    enablePhysics = false;
    const int wallSides = 5;
    // const float wallHeight = 100.0f;
    const float wallWidth = 500.0f;
    float wallAngle = 360.0f / wallSides;
    float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    wallDist *= 0.8f;
    for(float angle = 0.0f; angle < 360.0f; angle += wallAngle)
    {
        // 3 balloons on each wall
        balloons.push_back({
            static_cast<BallonColor>(std::rand() % 5),
            glm::vec3(-wallDist * std::sin(glm::radians(angle)), 15.0f, -wallDist * std::cos(glm::radians(angle))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(std::rand() % 5),
            glm::vec3(-wallDist * std::sin(glm::radians(angle+wallAngle/4.0f)), 15.0f, -wallDist * std::cos(glm::radians(angle+wallAngle/4.0f))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(std::rand() % 5),
            glm::vec3(-wallDist * std::sin(glm::radians(angle-wallAngle/4.0f)), 15.0f, -wallDist * std::cos(glm::radians(angle-wallAngle/4.0f))),
            glm::vec3(0.0f),
            8.0f
        });
    }
}

// the following two helper functions load distinct random color
std::vector<int> loadVector()
{
    std::vector<int> v{0, 1, 2, 3, 4};
    std::random_shuffle(v.begin(), v.end());
    return v;
}
int custom_rand_color()
{
    static std::vector<int> v{loadVector()};
    static size_t index{0};
    int color = v[index];
    index++;
    // reset index and shuffle again
    if(index >= v.size())
    {
        v = loadVector();
        index = 0;
    }
    return color;
}

void ParticleBalloon::loadBalloonsStage2()
{
    // load balloons on every wall
    // ask player to shoot the RED ones
    balloons.clear();
    balloons.resize(0);
    enablePhysics = false;
    const int wallSides = 5;
    // const float wallHeight = 100.0f;
    const float wallWidth = 500.0f;
    float wallAngle = 360.0f / wallSides;
    float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    wallDist *= 0.8f;
    for(float angle = 0.0f; angle < 360.0f; angle += wallAngle)
    {
        // 6 balloons on each wall
        balloons.push_back({
            static_cast<BallonColor>(custom_rand_color()),
            glm::vec3(-wallDist * std::sin(glm::radians(angle)), 25.0f, -wallDist * std::cos(glm::radians(angle))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(custom_rand_color()),
            glm::vec3(-wallDist * std::sin(glm::radians(angle+wallAngle/4.0f)), 25.0f, -wallDist * std::cos(glm::radians(angle+wallAngle/4.0f))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(custom_rand_color()),
            glm::vec3(-wallDist * std::sin(glm::radians(angle-wallAngle/4.0f)), 25.0f, -wallDist * std::cos(glm::radians(angle-wallAngle/4.0f))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(custom_rand_color()),
            glm::vec3(-wallDist * std::sin(glm::radians(angle)), 0.0f, -wallDist * std::cos(glm::radians(angle))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(custom_rand_color()),
            glm::vec3(-wallDist * std::sin(glm::radians(angle+wallAngle/4.0f)), 0.0f, -wallDist * std::cos(glm::radians(angle+wallAngle/4.0f))),
            glm::vec3(0.0f),
            8.0f
        });
        balloons.push_back({
            static_cast<BallonColor>(custom_rand_color()),
            glm::vec3(-wallDist * std::sin(glm::radians(angle-wallAngle/4.0f)), 0.0f, -wallDist * std::cos(glm::radians(angle-wallAngle/4.0f))),
            glm::vec3(0.0f),
            8.0f
        });
    }
}

void ParticleBalloon::loadBalloonsStage3()
{
    // appears everywhere
    const int num = 20;
    balloons.clear();
    balloons.resize(0);
    enablePhysics = true;
}

void ParticleBalloon::loadBalloonsStage4()
{
    // appears everywhere
    const int num = 50;
    balloons.clear();
    balloons.resize(0);
    enablePhysics = true;
    enableWindForce = true;
}

// helper function to load normal vector information for walls
std::vector<glm::vec3> loadWallNormals()
{
    const int wallSides = 5;
    // const float wallHeight = 100.0f;
    // const float wallWidth = 500.0f;
    float wallAngle = 360.0f / wallSides;
    // float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    std::vector<glm::vec3> n;
    for(int i = 0; i < wallSides; i++)
    {
        glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(wallAngle * i), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 localN = glm::normalize(glm::vec3(transform * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
        n.push_back(localN);
    }
    return n;
}
// helper function to load points on each wall, for distance calculation
std::vector<glm::vec3> loadWallPoints()
{
    const int wallSides = 5;
    // const float wallHeight = 100.0f;
    const float wallWidth = 500.0f;
    float wallAngle = 360.0f / wallSides;
    float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    std::vector<glm::vec3> p;
    for(int i = 0; i < wallSides; i++)
    {
        glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(wallAngle * i), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 localP = glm::vec3(transform * glm::vec4(0.0f, 0.0f, -wallDist, 1.0f));
        p.push_back(localP);
    }
    return p;
}

void ParticleBalloon::update(int fps)
{
    if(!enablePhysics) return; // if physics not enabled, no update is needed
    float deltaTime = 1.0f / fps;
    const float groundLevel = -50.0f;
    const float bounceCoeff = 1.0f; // reference: https://physics.stackexchange.com/questions/256468/model-formula-for-bouncing-ball
    // the only force to consider is the gravity
    glm::vec3 deltaVel{0.0f, -GRAVITY_G * deltaTime, 0.0f};
    // TODO: add necessary wind force

    // wall information
    static std::vector<glm::vec3> wallNormals{loadWallNormals()};
    static std::vector<glm::vec3> wallPoints{loadWallPoints()};
    for(size_t i = 0; i < balloons.size(); i++)
    {
        auto& b1{balloons[i]};
        b1.vel += deltaVel;
        b1.pos += b1.vel * deltaTime;
        // consider bouncing on the ground
        if(b1.pos.y-b1.radius <= groundLevel) b1.vel = glm::reflect(b1.vel, glm::vec3(0.0f, 1.0f, 0.0f)) * bounceCoeff;
        // consider bouncing on the walls
        for(size_t wall = 0; wall < wallNormals.size(); wall++)
        {
            // reference: https://mathinsight.org/distance_point_plane
            auto& p1 = wallPoints[wall*2];
            auto& p2 = b1.pos;
            auto& n = wallNormals[wall];
            float D = -glm::dot(n, p1);
            float d = std::abs(D + glm::dot(n, p2)); // length of normal is set to 1
            if(d <= b1.radius) b1.vel = glm::reflect(b1.vel, n) * bounceCoeff;
        }
        // consider bouncing with other balloons
        for(size_t j = 0; j < balloons.size(); j++)
        {
            if(i == j) continue;
            auto& b2{balloons[j]};
            glm::vec3 dir = b1.pos - b2.pos;
            float dist = glm::length(b1.pos - b2.pos);
            if(dist <= (b1.radius + b2.radius))
            {
                // collision detected
                // reference: https://stackoverflow.com/questions/345838/ball-to-ball-collision-detection-and-handling
                dir /= dist;
                float b1ci = glm::dot(b1.vel, dir);
                float b2ci = glm::dot(b2.vel, dir);
                // assume same mass
                b1.vel += (b2ci - b1ci) * dir;
                b2.vel += (b1ci - b2ci) * dir;
            }
        }
    }
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