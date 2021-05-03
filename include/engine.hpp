// This header defines the GameEngine class
#pragma once

#include "camera.hpp"
#include <irrKlang.h>

#include <string>
#include <vector>
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

    Camera* camera;
    int winW, winH;
    int mouseX, mouseY;
    bool viewControl;
    std::vector<std::pair<std::string, int>> helpMessage;
    std::vector<std::pair<std::string, unsigned>> textures;
    unsigned textureActiveID;

    // gun animation specific
    float gunUpDegree = 0.0f; // range: 0.0f to 30.0f
    unsigned short gunUpState = 0; // 0 for no move, 1 for moving up, 2 for moving down

    // audio device
    irrklang::ISoundEngine* audioEngine;
    irrklang::ISound* musicBackground;

private:
    // rendering functions
    void renderEnv();
    void renderGun();
};