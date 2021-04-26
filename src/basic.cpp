#include "basic.hpp"

void setup()
{
    // first time init game engine object
    auto engine = GameEngine::instance();
    engine->setup();
}

void renderScene()
{

}

void update(int value)
{

}

void handleKeyboard(unsigned char key, int x, int y)
{
    auto engine = GameEngine::instance();
    switch(key)
    {
        case 27:
            exit(0);
            break;
        default: break;
    }
    engine->handleKeyboard(key);
}