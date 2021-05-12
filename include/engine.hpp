// This header defines the GameEngine class
#pragma once

#include "camera.hpp"
#include "particle.hpp"
#include "state.hpp"
#include <irrKlang.h>

#include <string>
#include <vector>

enum AnimState
{
    DEFAULT  = 0,
    FORWARD  = 1,
    BACKWARD = 2,
};

// custom animation data
// created for animations (move to a position and move back)
struct AnimData
{
    float data; // current data
    float start; // minimum
    float end; // maximum
    float step; // step
    AnimState state;
};

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    static GameEngine* instance();
    void setup();
    void renderGame();
    void renderInterface();
    void updateLogics(int frameNum);
    void updateWindowSize(int w, int h);
    void handleKeyboard(unsigned char key);
    void handleMouseClick(bool isDown, bool isLeft);
    void handleMouseMotion(int x, int y);

    int fps = 60;

private:
    void addHelpMessage(const std::string message, int timeout);
    void enterViewControl();
    void exitViewControl();
    void loadTextures();
    bool raycast(const glm::vec3& origin, const glm::vec3& dir, float& t);

    Camera* camera;
    int winW, winH;
    int mouseX, mouseY;
    bool viewControl;
    std::vector<std::pair<std::string, int>> helpMessage;
    std::vector<std::pair<std::string, unsigned>> textures;
    unsigned textureActiveID;
    GameState state;
    std::string gameGuide; // game guide appears upper middle screen

    // gun animation specific
    glm::vec3 gunPos;
    AnimData gunUpDegree{0.0f, 0.0f, 30.0f, 5.0f, AnimState::DEFAULT};
    AnimData gunAimR{2.5f, 0.0f, 2.5f, 0.5f, AnimState::DEFAULT};
    AnimData gunAimD{8.0f, 6.0f, 8.0f, 0.4f, AnimState::DEFAULT};
    ParticleBullet bullets;

    // audio device
    irrklang::ISoundEngine* audioEngine;
    irrklang::ISound* musicBackground;

    // particles
    ParticleBalloon* balloons;
    std::vector<Firework*> fireworks;

private:
    // rendering functions
    void renderEnv();
    void renderGun();
    void renderBullets();
    void renderBalloons();
    void renderFireworks();
};