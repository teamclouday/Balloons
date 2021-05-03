// This header defines the GameEngine class
#pragma once

#include "camera.hpp"

#include <string>
#include <vector>
#include <iostream>
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

private:
    // rendering functions
    void renderEnv();
    void renderGun();
};