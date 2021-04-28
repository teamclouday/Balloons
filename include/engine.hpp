// This header defines the GameEngine class
#pragma once

#include "camera.hpp"

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

    int fps = 60;

private:
    void enterViewControl();
    void exitViewControl();

    Camera* camera;
    int winW, winH;
    bool viewControl;
    std::vector<std::string> helpMessage;
};