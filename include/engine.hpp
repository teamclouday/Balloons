// This header defines the GameEngine class
#pragma once

#include "camera.hpp"

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    static GameEngine* instance();
    void setup();
    void handleKeyboard(unsigned char key);


private:
    void enterViewControl();
    void exitViewControl();

    Camera* camera;
    int winW, winH;
    bool viewControl;
};